#ifndef cqder_DEBUG_H_
#define cqder_DEBUG_H_

#include <iostream>
#include "color.h"

// macros to help debug with foo method
#ifdef DEBUG_MODE // on compilation with DEBUG_MODE=Y
	#define WHEREAMI std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " << __PRETTY_FUNCTION__ << std::endl;
	#define VAR(X) #X<<" = "<<X
	#define PRINT(X) std::cerr<< color::red << color::bold <<#X<<" : "<<color::end <<X<<std::endl;
#else
	#define WHEREAMI
	#define VAR(X) ""
	#define PRINT(X) 
#endif



#endif
