// --- OPERATORS -------------------------------------------------------
color::color & color::color::operator = ( const color & c )
{
	if ( this != &c )
		{ flag = c.flag; }
	return *this;
}

color::color::operator std::string () const
{
	return flag;
}
color::color::operator const char* () const
{
	return flag.c_str();
}

// --- GETTERS ---------------------------------------------------------
const std::string color::color::str () const
{
	return "\033[" + flag + "m";
}
const char * color::color::c_str () const
{
	return ("\033[" + flag + "m").c_str();
}

// --- OPERATORS -------------------------------------------------------
std::ostream & operator << ( std::ostream & o , const color::color & c )
{
	o << c.flag;
	return o;
}
std::ofstream & operator << ( std::ofstream & f , const color::color & )
{
	return f;
}
