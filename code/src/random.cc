#include "random.h"

namespace cqder_random
{
	std::random_device               __cqder_rd;
	std::mt19937                     __cqder_gen( __cqder_rd() );
	std::uniform_real_distribution<> __cqder_dis(0,1);
}
