#ifndef cqder_TOOLS_H_
#define cqder_TOOLS_H_

#include <iostream>
#include <ostream>
#include <iterator>
#include <algorithm>
#include <functional>

/**
.. cpp:namespace tools

	Namespace for all general tools of ``cqder`` framework, STL-like.
**/
namespace tools
{

	/**
	.. cpp:function: template<typename Iterator> void display ( const Iterator begin , const Iterator end , std::basic_ostream<char> & out=std::cout , const std::string & sep=" " )

		Display a container between two iterators. Contained type must to overload operator ``<<``.

		.. cpp:var:: const Iterator begin

			Begining iterator

		.. cpp:var:: const Iterator end

			Ending iterator

		.. cppr:var:: std::basic_ostream<char> & out

			Output stream, :cpp:var:`std::cout` by default.

		.. cpp:var:: const std::string & sep

			Separator value, a space by default.

	**/
	template < typename Iterator >
	void
	display ( const Iterator begin , const Iterator end , std::basic_ostream<char> & out=std::cout , const std::string & sep=" " )
	{
		typedef typename std::iterator_traits<Iterator>::value_type T; // determine the pointed type
		std::copy( begin , end , std::ostream_iterator< T >( out , sep.c_str() ) );
	}

	/**
	.. cpp:function template<typename Iterator, typename InternalFunction> void for_each ( Iterator begin , const Iterator end , InternalFunction f )

		Apply an internal function on each element of a container.

		.. cpp:var:: Iterator begin

			Begining iterator.

		.. cpp:var:: Iterator end

			Ending iterator.

		.. cpp:var:: InternalFunction f

			Pointer on an internal function of contained type.
	**/
	template < typename Iterator , typename InternalFunction >
	void
	for_each ( Iterator begin , const Iterator end , InternalFunction f )
	{
		while ( begin != end )
		{
			begin->f(); ++begin;
		}
	}

	/**
	.. cpp:struct:: increment<T>

		Fonctor to generate vector with incremental value

		.. cpp:member:: T value

			Current value.

		.. cpp:member:: T incremental_value

			Step of incrementation.


		.. cpp:function:: increment::increment ( T init=0 , T inc=1 )

			The only constructor of this functor, with default value.

		.. cpp:function:: inline T increment::operator () ()

			Operator which return the incremented value.
	**/
	template < typename T >
	struct increment
	{
		T value;
		T incremental_value;

		// CONSTRUCTOR
			increment ( T init=0 , T inc=1 ) :
				value(init) , incremental_value(inc)
			{ ; }

		// OPERATOR
			inline T operator () ()
			{
				T tmp = value;
				value+=incremental_value;
				return tmp;
			}
	};

	/*!
	.. cpp:function:: template<typename Iterator> void range ( Iterator first , Iterator last , typename std::iterator_traits<Iterator>::value_type value=0 , typename std::iterator_traits<Iterator>::value_type step=1 )
	!*/
	template < typename Iterator >
	void
	range ( Iterator first , Iterator last , typename std::iterator_traits<Iterator>::value_type value=0 , typename std::iterator_traits<Iterator>::value_type step=1 )
	{
		for ( ; first!=last ; ++first )
		{
			*first = value;
			value += step;
		}
	}

	/*!
	.. cpp:struct:: template<typename Iterator , typename UnaryFunc> transform_iterator<Iterator,UnaryFunc>
	!*/
#define iterator_type(X) typename std::iterator_traits<X>::value_type
template < typename Iterator , typename UnaryFunc=std::function<iterator_type(Iterator)(iterator_type(Iterator))> >
#undef iterator_type
	struct transform_iterator
	{
		typedef typename std::iterator_traits<Iterator>::value_type                iterator_value_type;

		// iterator_traits
		typedef typename std::iterator_traits<Iterator>::difference_type  	       difference_type;
		typedef typename std::result_of<UnaryFunc( iterator_value_type )>::type    value_type;
		typedef const value_type*                                         	       pointer;
		typedef const value_type&                                         	       reference;
		typedef std::bidirectional_iterator_tag                                    iterator_category;

		private :
			Iterator _itr;
			UnaryFunc _func;

		public :

			transform_iterator ( const transform_iterator<Iterator,UnaryFunc> & );
			transform_iterator ( const Iterator , UnaryFunc );

			~transform_iterator ();

			inline transform_iterator<Iterator,UnaryFunc> & operator = ( const transform_iterator<Iterator,UnaryFunc> & );

			inline transform_iterator<Iterator,UnaryFunc> & operator ++ ();
			inline transform_iterator<Iterator,UnaryFunc>   operator ++ (int);

			inline transform_iterator<Iterator,UnaryFunc> & operator -- ();
			inline transform_iterator<Iterator,UnaryFunc>   operator -- (int);

			inline value_type operator * () const;

			inline bool operator == ( const transform_iterator<Iterator,UnaryFunc> & ) const;
			inline bool operator == ( const Iterator &                               ) const;

			inline bool operator != ( const transform_iterator<Iterator,UnaryFunc> & ) const;
			inline bool operator != ( const Iterator &                               ) const;

			inline bool operator <  ( const transform_iterator<Iterator,UnaryFunc> & ) const;
			inline bool operator <  ( const Iterator &                               ) const;

			inline bool operator >  ( const transform_iterator<Iterator,UnaryFunc> & ) const;
			inline bool operator >  ( const Iterator &                               ) const;

			inline bool operator <= ( const transform_iterator<Iterator,UnaryFunc> & ) const;
			inline bool operator <= ( const Iterator &                               ) const;

			inline bool operator >= ( const transform_iterator<Iterator,UnaryFunc> & ) const;
			inline bool operator >= ( const Iterator &                               ) const;

			inline difference_type operator - ( const transform_iterator<Iterator,UnaryFunc> & ) const;
			inline difference_type operator - ( const Iterator &                               ) const;
	};

	#include "transform_iterator.txx"

} // namespace tools

#endif
