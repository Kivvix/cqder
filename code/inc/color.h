#ifndef cqder_COLOR_H_
#define cqder_COLOR_H_

#include <iostream>
#include <string>

/**
 * \namespace color
 * \brief Strings of characters for colorized text into terminal
 **/
namespace color
{

	struct color
	{
		std::string flag;

	// CONSTRUCTOR
		color ();
		color ( const color & );

		explicit color ( const std::string & );
		explicit color ( const char* );

	// DESTRUCTOR
		virtual ~color ();

	// OPERATORS
		inline color & operator = ( const color & );

		inline operator std::string () const;
		inline operator const char* () const;

	// GETTERS
		inline const std::string str   () const;
		inline const char *      c_str () const;
	};


// source des codes couleurs : http://misc.flogisoft.com/bash/tip_colors_and_formatting
extern const color default_color;
extern const color red;
extern const color green;
extern const color yellow;
extern const color blue;
extern const color mangenta;
extern const color cyan;

extern const color bold;
extern const color underl;
extern const color reverse;
extern const color endb;
extern const color endu;
extern const color endr;

extern const color end;

} // namespace color

inline std::ostream  & operator << ( std::ostream  & , const color::color & );
inline std::ofstream & operator << ( std::ofstream & , const color::color & );

#include "color.inl"

#endif
