#ifndef cqder_RANDOM_H_
#define cqder_RANDOM_H_

#include <random>

namespace cqder_random
{
	extern std::random_device               __cqder_rd;
	extern std::mt19937                     __cqder_gen;
	extern std::uniform_real_distribution<> __cqder_dis;
}


#define random_if(X)    if ( cqder_random::__cqder_dis(cqder_random::__cqder_gen) < X )

#endif
