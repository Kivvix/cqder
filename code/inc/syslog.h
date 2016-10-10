#ifndef cqder_SYSLOG_H_
#define cqder_SYSLOG_H_

#include <iostream>
#include <fstream>
#include <exception>
#include <ctime>
#include <iomanip>
#include <exception>

#include "color.h"

namespace syslog
{

	/**
	\fn date
	\brief return the date into a stream in format : yyyy-mm-dd
	**/
	std::ostream & date ( std::ostream & );
	/**
	\fn hour
	\brief return the hour into a stream in format : HH:MM::SS
	**/
	std::ostream & hour ( std::ostream & );

	/**
	\struct level
	\brief Décrit les niveaux de log
	**/
	struct level
	{
		public :
	// ATTRIBUT
			std::string   flag;
			color::color  color;
			unsigned char priority; // 0 to 255

	// CONSTRUCTOR
			level ( std::string f="ERROR" , color::color c=color::red , unsigned char p=255 );
			level ( const level & );

	// DESTRUCTOR
			virtual ~level ();

	// OPERATOR
			level & operator = ( const level & );
	};

// CONST VAR ---------------------------------------------------------
extern const level low;
extern const level note;
extern const level info;
extern const level warning;
extern const level error;

} //namespace syslog

// OPERATORS ---------------------------------------------------------
bool operator <  ( syslog::level , syslog::level );
bool operator >  ( syslog::level , syslog::level );
bool operator <= ( syslog::level , syslog::level );
bool operator >= ( syslog::level , syslog::level );

std::ofstream & operator << ( std::ofstream & , const syslog::level & );
std::ostream  & operator << ( std::ostream  & , const syslog::level & );

namespace syslog
{
	/**
	\struct syslog
	\brief Flux permettant simplement l'écriture de logs dans un fichier et le flux d'erreurs
	**/
	struct syslog : public std::ostream
	{
		public :
			std::ofstream file;
			level         log_level;

	// CONSTRUCTOR
			syslog ( std::string fic="log.log" , level l=low );

	// DESTRUCTOR
			~syslog ();

	// METHODS
		template <typename T>
			void log ( T );
		template <typename T>
			void log ( level , T );
		template <typename T>
			void log ( level , T , bool );
	};

} // namespace syslog

// OPERATORS ---------------------------------------------------------
template <typename T>
syslog::syslog & operator << ( syslog::syslog & , const T & );

template <>
syslog::syslog & operator << ( syslog::syslog & , const syslog::level & );
template <>
syslog::syslog & operator << ( syslog::syslog & , const color::color & );
template <>
syslog::syslog & operator << ( syslog::syslog & , const std::exception & );

syslog::syslog & operator << ( syslog::syslog & , std::ostream& (*os)(std::ostream&) );


/// TEMPLATE /////////////////////////////////////////////////////////

namespace syslog
{
// METHODS -----------------------------------------------------------
//____________________________________________________________________
	template <typename T>
	void syslog::log ( T message )
	{
		*this << log_level << " " << message << std::endl;
	}

//____________________________________________________________________
	template <typename T>
	void syslog::log ( level l , T message )
	{
		if ( l >= log_level )
		{
			*this << l << " " << message << std::endl;
		}
	}

//____________________________________________________________________
	template <typename T>
	void syslog::log ( level l , T message , bool condition)
	{
		if ( l >= log_level && condition )
		{
			*this << l << " " << message << std::endl;
		}
	}

} // namespace syslog

// OPERATORS ---------------------------------------------------------
template <typename T>
syslog::syslog & operator << ( syslog::syslog & log , const T & data )
{
	std::clog << data;
	log.file  << data;
	return log;
}


#endif
