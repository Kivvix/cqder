#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <sys/time.h>

//#define DEBUG_MODE

#include "tools.h"
#include "debug.h"
#include "syslog.h"
#include "color.h"
#include "benchmark.h"

const std::size_t n = (1<<18) + 5;
const std::size_t loop = 1000;

tools::increment<double> inc;

//____________________________________________________________________
cqder_benchmark(generate,loop)
{
	std::vector<double> a(n);
	std::generate( a.begin(), a.end(), inc );
}
//____________________________________________________________________
cqder_benchmark(for,loop)
{
	std::vector<double> a(n);
	for ( std::size_t i=0 ; i<n ; ++i )
		{ a[i]=inc(); }
}
//____________________________________________________________________
cqder_benchmark(while,loop)
{
	std::vector<double> a(n);
	std::size_t i=0;
	while ( i<n )
		{ a[i++] = inc(); }
}
//____________________________________________________________________
cqder_benchmark(push_back,loop)
{
	std::vector<double> a;
	for ( unsigned int i=0 ; i<n ; ++i )
		{ a.push_back(inc()); }
}
//____________________________________________________________________
cqder_benchmark(reserve,loop)
{
	std::vector<double> a; a.reserve(n);
	for ( std::size_t i=0 ; i<n ; ++i )
		{ a.push_back(inc()); }
}
//____________________________________________________________________
cqder_benchmark(iterator,loop)
{
	std::vector<double> a(n);
	for ( std::vector<double>::iterator it=a.begin() ; it != a.end() ; ++it )
		{ *it = inc(); }
}
//____________________________________________________________________
cqder_benchmark(iterator_end,loop)
{
	std::vector<double> a(n);
	const std::vector<double>::iterator end = a.end();
	for ( std::vector<double>::iterator it=a.begin() ; it != end ; ++it )
		{ *it = inc(); }
}

int main ()
{
	PRINT(n);
	benchmark::launch(benchmark::option::stream);
	return 0;
}
