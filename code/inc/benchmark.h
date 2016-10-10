#ifndef cqder_BENCHMARK_H_
#define cqder_BENCHMARK_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <functional>
#include <valarray>
#include <list>

#include <sys/time.h>

/**
.. cpp:namespace:: benchmark
	
	All concerning benchmark stuff.
**/
namespace benchmark
{
	/**
	.. cpp:enum:: option

		Enumeration for benchmark options
	**/
	enum struct option { file , stream };

	/**
	.. cpp:class:: __cqder_benchmark_model

		Mother class for benchmark tests, and display statistics of runs

		.. cpp:member:: std:size_t __cqder_benchmark_model::_n_iter

			Describe the number of iteration for a complete bencmark test

		.. cpp:member:: std::string __cqder_benchmark_model::_benchmark_name

			Save the benchmark name, only for displaying into :cpp:func:`__cqder_benchmark_model::stat`.

		.. cpp:member:: static std::list< __cqder_benchmark_model * > _instance_list

			Static list of instances of :cpp:class:`__cqder_benchmark_model` for :cpp:func:`benchmark::launch`.


		.. cpp:function:: __cqder_benchmark_model::__cqder_benchmark_model ()

			Default constructor. It adds ``*this`` to the list of instances to launch all benchmark test with :cpp:func:`benchmark::launch`.

		.. cpp:function:: __cqder_benchmark_model::~__cqder_benchmark_model ()

			Virtual destructor.

		.. cpp:function:: virtual void __cqder_benchmark_model::benchmark_code () const =0

			Function contains benchmark code. It works like ``google_test`` macros. This internal function will be overloaded in each daughter of this class.

		.. cpp:function:: virtual void run ( std::ostream & os=std::cout ) const

			Function which runs this benchmark test (loop of :cpp:member:`__cqder_benchmark_model::_n_iter` iterations) and save time of each iteration and compute some statistics on them.

		.. cpp:function:: void stat ( std::ostream & , const std::valarray<double> & ) const

			Compute and display stat into the output stream. The valarray contains times.

	**/
	class __cqder_benchmark_model
	{
		protected:
			std::size_t _n_iter;
			std::string _benchmark_name;
			static std::list< __cqder_benchmark_model * > _instance_list;

		public:
			__cqder_benchmark_model ();
			virtual ~__cqder_benchmark_model () { ; }

			virtual void benchmark_code () const =0;

			virtual void run ( option , std::ostream & os=std::cout ) const;
			void stat_file   ( std::ostream & , const std::valarray<double> & ) const;
			void stat_stream ( std::ostream & , const std::valarray<double> & ) const;
			void stat ( option , std::ostream & , const std::valarray<double> & ) const;

		protected:
			static void launch_file   ();
			static void launch_stream ( std::ostream & os=std::cout );

		friend void launch ( option , std::ostream & );
	};

	/**

	.. cpp:function:: void launch ( std::ostream & os=std::cout )

		Function to launch all benchmarm tests.
	**/
	void launch ( option , std::ostream & os=std::cout );

} // benchmark


/**
.. c:macro:: cqder_benchmark

	This macro is helper for benchmark test code. An example is following::

		cqder_benchmark ( test_generate , 100 )
		{
			std::vector<double> v(1024);
			std::generate( v.begin() , v.end() ,
				[](){ static int i=0; ++i; return 42/i; }
			);
		}


.. cpp:class:: __cqder_##bench_name##_BENCH

	Class generates by :c:macro:`cqder_benchmark`, it's a daughter of :cpp:class:`__cqder_benchmark_model`. One instance of this class is build, and it will be run with :cpp:func:`benchmark::launch`.

**/
#define cqder_benchmark( bench_name , n_iter ) \
class __cqder_##bench_name##_BENCH : public benchmark::__cqder_benchmark_model \
{\
	public:\
		__cqder_##bench_name##_BENCH() { _n_iter = n_iter; _benchmark_name = #bench_name; }\
\
		inline void benchmark_code () const;\
};\
__cqder_##bench_name##_BENCH var_##bench_name;\
void __cqder_##bench_name##_BENCH::benchmark_code() const


#endif
