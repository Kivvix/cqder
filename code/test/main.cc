#include <gtest/gtest.h>
#include "all_tests.h"

int main(int argc,char** argv)
{
	std::cout << "\033[36m[||||||||||]\033[0m Test of CQDER project\n" << std::endl;
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
