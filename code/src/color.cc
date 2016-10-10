#include "color.h"

// --- CONSTRUCTORS ----------------------------------------------------
color::color::color ( const std::string & f ) :
	flag(f)
{ ; }

color::color::color ( const char* s ) :
	flag(s)
{ ; }

color::color::color ( const color & c ) :
	flag(c.flag)
{ ; }

// --- DESTRUCTOR ------------------------------------------------------
color::color::~color ()
{ ; }

// --- CONSTANTS -------------------------------------------------------
const color::color color::default_color = color("\033[39m");
const color::color color::red      = color("\033[31m");
const color::color color::green    = color("\033[32m");
const color::color color::yellow   = color("\033[33m");
const color::color color::blue     = color("\033[34m");
const color::color color::mangenta = color("\033[35m");
const color::color color::cyan     = color("\033[36m");

const color::color color::bold     = color("\033[1m");
const color::color color::underl   = color("\033[4m");
const color::color color::reverse  = color("\033[7m");
const color::color color::endb     = color("\033[21m");
const color::color color::endu     = color("\033[24m");
const color::color color::endr     = color("\033[27m");

const color::color color::end      = color("\033[0m");
