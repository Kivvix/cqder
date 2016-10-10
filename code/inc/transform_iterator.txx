/**
	\file transform_iterator.txx
	\brief Implémentation de la classe transform_iterator<Iterator,UnaryFunc>
**/


//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
transform_iterator<Iterator,UnaryFunc>::transform_iterator ( const transform_iterator<Iterator,UnaryFunc> & a ) :
	_itr(a._itr) , _func(a._func)
{ ; }

//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
transform_iterator<Iterator,UnaryFunc>::transform_iterator ( const Iterator it , UnaryFunc func ) :
	_itr(it) , _func(func)
{ ; }

//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
transform_iterator<Iterator,UnaryFunc>::~transform_iterator ()
{ ; }

//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
transform_iterator<Iterator,UnaryFunc> &
transform_iterator<Iterator,UnaryFunc>::operator = ( const transform_iterator<Iterator,UnaryFunc> & a )
{
	if ( &a != this )
	{
		_itr = a._itr;
		_func  = a._func;
	}
	return *this;
}

//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
transform_iterator<Iterator,UnaryFunc> &
transform_iterator<Iterator,UnaryFunc>::operator ++ ()
	{ ++_itr; return *this; }
//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
transform_iterator<Iterator,UnaryFunc>
transform_iterator<Iterator,UnaryFunc>::operator ++ (int)
	{ transform_iterator tmp = *this; ++_itr; return tmp; }

//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
transform_iterator<Iterator,UnaryFunc> &
transform_iterator<Iterator,UnaryFunc>::operator -- ()
	{ --_itr; return *this; }
//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
transform_iterator<Iterator,UnaryFunc>
transform_iterator<Iterator,UnaryFunc>::operator -- (int)
	{ transform_iterator tmp = *this; --_itr; return tmp; }


//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
typename transform_iterator<Iterator,UnaryFunc>::value_type
transform_iterator<Iterator,UnaryFunc>::operator * () const
	{ return _func(*_itr); }


//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
bool
transform_iterator<Iterator,UnaryFunc>::operator == ( const transform_iterator<Iterator,UnaryFunc> & a ) const
	{ return _itr == a._itr; }
//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
bool
transform_iterator<Iterator,UnaryFunc>::operator == ( const Iterator & a ) const
	{ return _itr == a; }

//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
bool
transform_iterator<Iterator,UnaryFunc>::operator != ( const transform_iterator<Iterator,UnaryFunc> & a ) const
	{ return _itr != a._itr; }
//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
bool
transform_iterator<Iterator,UnaryFunc>::operator != ( const Iterator & a ) const
	{ return _itr != a; }

//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
bool
transform_iterator<Iterator,UnaryFunc>::operator <  ( const transform_iterator<Iterator,UnaryFunc> & a ) const
	{ return _itr <  a._itr; }
//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
bool
transform_iterator<Iterator,UnaryFunc>::operator <  ( const Iterator & a ) const
	{ return _itr <  a; }

//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
bool
transform_iterator<Iterator,UnaryFunc>::operator >  ( const transform_iterator<Iterator,UnaryFunc> & a ) const
	{ return _itr >  a._itr; }
//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
bool
transform_iterator<Iterator,UnaryFunc>::operator >  ( const Iterator & a ) const
	{ return _itr >  a; }

//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
bool
transform_iterator<Iterator,UnaryFunc>::operator <= ( const transform_iterator<Iterator,UnaryFunc> & a ) const
	{ return _itr <= a._itr; }
//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
bool
transform_iterator<Iterator,UnaryFunc>::operator <= ( const Iterator & a ) const
	{ return _itr <= a; }

//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
bool
transform_iterator<Iterator,UnaryFunc>::operator >= ( const transform_iterator<Iterator,UnaryFunc> & a ) const
	{ return _itr >= a._itr; }
//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
bool
transform_iterator<Iterator,UnaryFunc>::operator >= ( const Iterator & a ) const
	{ return _itr >= a; }


//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
typename transform_iterator<Iterator,UnaryFunc>::difference_type
transform_iterator<Iterator,UnaryFunc>::operator - ( const transform_iterator<Iterator,UnaryFunc> & a ) const
	{ return _itr - a._itr; }
//____________________________________________________________________
template< typename Iterator, typename UnaryFunc >
typename transform_iterator<Iterator,UnaryFunc>::difference_type
transform_iterator<Iterator,UnaryFunc>::operator - ( const Iterator & a ) const
	{ return _itr - a; }
