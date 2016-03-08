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
		size_t newSize = m_size + sizeof( T );
		char* newVector = new char[ newSize ];
		if( newVector != nullptr )
		{
			std::memcpy( newVector, m_vector, m_size );
			std::memcpy( newVector + m_size, &element, sizeof( T ) );
			clear();
			m_size = newSize;
			m_vector = newVector;
			return true;
		}
		return false;
	}

	template< typename T >
	T pop( void ) const
	{
		T element;
		if( m_cursor + sizeof( T ) <= m_size )
		{
			memcpy( &element, m_vector + m_cursor, sizeof( T ) );
			m_cursor += sizeof( T );
		}
		else
		{
			m_cursor = m_size;
		}
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

	char* m_vector;

	size_t m_size;

	mutable size_t m_cursor;
};

#endif /* UNTYPEDSTACK_H_ */
