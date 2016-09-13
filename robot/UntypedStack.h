/*
 * UntypedStack.h
 *
 *  Created on: 8 mars 2016
 *      Author: ulysse
 */

#ifndef UNTYPEDSTACK_H_
#define UNTYPEDSTACK_H_

#include <cstddef>
#include <cstring>

/**
 * \class UntypedStack
 * \brief A container that can stack variables of different types.
 * UntypedStack can be used to group variables regardless of their types. It can be
 * used as a parser to compress and uncompress data or as a variable list of arguments.
 * Usage
 * Variables can be pushed to the UntypedStack using the shift operator << :
 * stack << unsigned int( 2016 );
 * stack << float( 3.141592 );
 * Or in a more compact way :
 * stack << int( 1 ) << float( 0.5 ) << double( 0.25 );
 * Then the variables can be poped in the same order using the shift operator >> :
 * stack >> year;
 * stack >> pi;
 * Or in a more compact way :
 * stack >> x1 >> x2 >> x3;
 * \warning You must always pay attention to the types of variables when using the
 * << and >> operators. For example if you pushed a float( 3.141592 ) like in the
 * first example, the output variable (pi) must be exactly a float otherwise the
 * UntypedStack's data will be corrupted.
 */
class UntypedStack
{
public:

	UntypedStack();

	UntypedStack( const UntypedStack& stack );

	virtual ~UntypedStack();

	const UntypedStack& operator=( const UntypedStack& stack );

	bool empty( void ) const;

	size_t size( void ) const;

	void clear( void );

	template< typename T >
	bool push( T element )
	{
		return binary_push( &element, sizeof( T ) );
	}

	template< typename T >
	T pop( void ) const
	{
		T element;
		binary_pop( &element, sizeof( T ) );
		return element;
	}

	template< typename T >
	UntypedStack& operator<<( const T& element )
	{
		push< T >( element );
		return *this;
	}

	template< typename T >
	const UntypedStack& operator>>( T& element ) const
	{
		element = pop< T >();
		return *this;
	}

	template< typename T >
	friend UntypedStack& operator>>( const T& element, UntypedStack& stack )
	{
		return element << stack;
	}

	template< typename T >
	friend const UntypedStack& operator<<( T& element, const UntypedStack& stack )
	{
		return stack >> element;
	}

protected:

	bool binary_push( const void* src, size_t size );

	bool binary_pop( void* dst, size_t size ) const;

	void* m_vector;

	size_t m_size;

	mutable size_t m_cursor;
};

#endif /* UNTYPEDSTACK_H_ */
