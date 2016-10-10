#include "benchmark.h"

std::list< benchmark::__cqder_benchmark_model * > benchmark::__cqder_benchmark_model::_instance_list;

//____________________________________________________________________
benchmark::__cqder_benchmark_model::__cqder_benchmark_model ()
{ _instance_list.push_back(this); }

//____________________________________________________________________
void benchmark::__cqder_benchmark_model::run ( benchmark::option opt , std::ostream & os ) const
{
	struct timeval tbegin, tend;

	std::valarray<double>times_values(_n_iter);
	for ( std::size_t i=0 ; i < _n_iter ; ++i )
	{
		gettimeofday( &tbegin , NULL );

		benchmark_code();
		
		gettimeofday( &tend   , NULL );
		times_values[i] = ((double)( 1000 * ( tend.tv_sec - tbegin.tv_sec ) +
			(( tend.tv_usec - tbegin.tv_usec ) / 1000 ) )) / 1000.0;
	}
	stat( opt , os , times_values );
}

//____________________________________________________________________
void benchmark::__cqder_benchmark_model::stat_file ( std::ostream & os , const std::valarray<double> & times  ) const
{
	std::copy( std::begin(times) , std::end(times) , std::ostream_iterator<double>( os , "\n" ) );
}

//____________________________________________________________________
void benchmark::__cqder_benchmark_model::stat_stream ( std::ostream & os , const std::valarray<double> & times  ) const
{
	double sum = times.sum();
	double min = times.min();
	double max = times.max();

	os << std::fixed;
	os << std::left << std::setprecision(4) << std::setfill('0') << sum/times.size();
	os << "      "  << std::setprecision(3) << std::setfill('0') << min;
	os << "      "  << std::setprecision(3) << std::setfill('0') << max;
	os << "      "  << _benchmark_name << " (" << _n_iter << ")\n";
}

//____________________________________________________________________
void benchmark::__cqder_benchmark_model::stat ( benchmark::option opt , std::ostream & os , const std::valarray<double> & times ) const
{
	if ( opt == benchmark::option::file )
		{ stat_file( os , times ); }
	else
		{ stat_stream( os , times ); }
}

//____________________________________________________________________
void benchmark::__cqder_benchmark_model::launch_file ()
{
	std::list< benchmark::__cqder_benchmark_model * >::const_iterator beg = benchmark::__cqder_benchmark_model::_instance_list.begin();
	std::list< benchmark::__cqder_benchmark_model * >::const_iterator end = benchmark::__cqder_benchmark_model::_instance_list.end();
	
	for ( auto it = beg ; it != end ; ++it )
	{
		std::ofstream of ( (*it)->_benchmark_name + ".csv" );
		
		(*it)->run( benchmark::option::file , of);
		
		of.close();
	}
}

//____________________________________________________________________
void benchmark::__cqder_benchmark_model::launch_stream ( std::ostream & os )
{
	os << "   avg (s)" << "    min (s)" << "    max (s)" << std::endl;
	
	std::list< benchmark::__cqder_benchmark_model * >::const_iterator beg = benchmark::__cqder_benchmark_model::_instance_list.begin();
	std::list< benchmark::__cqder_benchmark_model * >::const_iterator end = benchmark::__cqder_benchmark_model::_instance_list.end();
	for ( auto it = beg ; it != end ; ++it )
		{ (*it)->run( benchmark::option::stream , os); }
}



//____________________________________________________________________
void benchmark::launch ( benchmark::option opt , std::ostream & os )
{
	if ( opt == benchmark::option::file )
		{ __cqder_benchmark_model::launch_file(); }
	else
		{ __cqder_benchmark_model::launch_stream(os); }
}
