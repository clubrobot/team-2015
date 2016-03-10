/*
 * UntypedStack.h
 *
 *  Created on: 8 mars 2016
 *      Author: ulysse
 */

#ifndef UNTYPEDSTACK_H_
#define UNTYPEDSTACK_H_

#include <cstddef>

class UntypedStack
{
public:

	UntypedStack();

	virtual ~UntypedStack();

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
