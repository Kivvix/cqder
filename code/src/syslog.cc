#include "syslog.h"

//____________________________________________________________________
// return the date into a stream in format : yyyy-mm-dd
std::ostream & syslog::date ( std::ostream & o )
{
	std::time_t  date = std::time(NULL);
	std::tm * date_tm = std::localtime(&date);
	
	return o << date_tm->tm_year+1900 << "-" << std::setw(2) << std::setfill('0') << date_tm->tm_mon+1 << "-" << std::setw(2) << std::setfill('0') << date_tm->tm_mday << "";
}

//____________________________________________________________________
// return the hour into a stream in format : HH:MM:SS
std::ostream & syslog::hour ( std::ostream & o )
{
	std::time_t  date = std::time(NULL);
	std::tm * date_tm = std::localtime(&date);
	
	return o << date_tm->tm_hour << ":" << std::setw(2) << std::setfill('0') << date_tm->tm_min << ":" << std::setw(2) << std::setfill('0') << date_tm->tm_sec << "";
}

// LEVEL =============================================================

// CONSTRUCTOR -------------------------------------------------------
syslog::level::level ( std::string f , color::color c , unsigned char p ) :
	flag(f) , color(c) , priority(p)
{ ; }

//____________________________________________________________________
syslog::level::level ( const level & l ) :
	flag(l.flag) , color(l.color) , priority(l.priority)
{ ; }

// DESTRUCTOR --------------------------------------------------------
syslog::level::~level ()
{ ; }

// OPERATOR ----------------------------------------------------------
syslog::level & syslog::level::operator = ( const level & l )
{
	if ( this != &l )
	{
		flag     = l.flag;
		color    = l.color;
		priority = l.priority;
	}
	return *this;
}

// boolean operators
//____________________________________________________________________
bool operator <  ( syslog::level a , syslog::level b )
{ return a.priority < b.priority; }
//____________________________________________________________________
bool operator >  ( syslog::level a , syslog::level b )
{ return a.priority > b.priority; }
//____________________________________________________________________
bool operator <= ( syslog::level a , syslog::level b )
{ return a.priority <= b.priority; }
//____________________________________________________________________
bool operator >= ( syslog::level a , syslog::level b )
{ return a.priority >= b.priority; }

//____________________________________________________________________
std::ofstream & operator << ( std::ofstream & f , const syslog::level & l )
{
	f << "[" << l.flag << "]";
	return f;
}

//____________________________________________________________________
std::ostream  & operator << ( std::ostream  & o , const syslog::level & l )
{
	o << l.color << "[" << l.flag << "]" << color::end;
	return o;
}

// --- CONST VAR -----------------------------------------------------
const syslog::level syslog::low     ( "LOW"     , color::cyan   , 0   );
const syslog::level syslog::note    ( "NOTE"    , color::green  , 64  );
const syslog::level syslog::info    ( "INFO"    , color::blue   , 128 );
const syslog::level syslog::warning ( "WARNING" , color::yellow , 192 );
const syslog::level syslog::error   ( "ERROR"   , color::red    , 255 );


// SYSLOG ============================================================

// CONSTRUCTOR -------------------------------------------------------
syslog::syslog::syslog ( std::string fic , level l ) :
	file(fic.c_str()) , log_level(l)
{
	if ( file.fail() )
		{ throw std::ios_base::failure("Can't open file : " + fic); }
		
	//TODO: modifier ces lignes car c'est moche en début de fichier
	file << "Syslog [" << date << " " << hour << "]" << std::endl;
	file << "--------------------" << std::endl;
}

// DESTRUCTOR --------------------------------------------------------
syslog::syslog::~syslog ()
{
//TODO: modifier ces lignes car c'est moche en fin de fichier
	file << "EOF" << std::endl;
	file << "[" << date << " " << hour << "]" << std::endl;
	
	file.close();
}

// OPERATOR ----------------------------------------------------------
template <>
syslog::syslog & operator << ( syslog::syslog & log , const syslog::level & l )
{
	std::clog << l.color << "[" << l.flag << "] " << color::end;
	log.file  << "[" << l.flag << "] ";
	return log;
}

//____________________________________________________________________
template <>
syslog::syslog & operator << ( syslog::syslog & log , const color::color & c )
{
	std::clog << c;
	return log;
}

//____________________________________________________________________
template <>
syslog::syslog & operator << ( syslog::syslog & log , const std::exception & e )
{
	std::clog << e.what();
	log.file  << e.what();
	return log;
}

//____________________________________________________________________
syslog::syslog & operator << ( syslog::syslog & log , std::ostream& (*os)(std::ostream&) )
{
	std::clog << os;
	log.file  << os;
	return log;
}
