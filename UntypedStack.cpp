/*
 * UntypedStack.cpp
 *
 *  Created on: 8 mars 2016
 *      Author: ulysse
 */

#include <cstdlib>
#include <cstring>

#include "UntypedStack.h"

UntypedStack::UntypedStack()
:	m_vector( nullptr )
,	m_size( 0 )
,	m_cursor( 0 )
{

}

UntypedStack::~UntypedStack()
{
	clear();
}

bool UntypedStack::empty( void ) const
{
	return ( m_vector == nullptr || m_size == 0 );
}

size_t UntypedStack::size( void ) const
{
	return m_size;
}

void UntypedStack::clear( void )
{
	if( m_vector != nullptr )
	{
		std::free( m_vector );
	}
	m_size = 0;
}

bool UntypedStack::binary_push( const void* src, size_t size )
{
	size_t newSize = m_size + size;
	void* newVector = std::malloc( newSize );
	if( newVector != nullptr )
	{
		std::memcpy( newVector, m_vector, m_size );
		std::memcpy( ( unsigned char* ) newVector + m_size, src, size );
		clear();
		m_size = newSize;
		m_vector = newVector;
		return true;
	}
	return false;
}

bool UntypedStack::binary_pop( void* dst, size_t size ) const
{
	if( m_cursor + size <= m_size )
	{
		std::memcpy( dst, ( unsigned char* ) m_vector + m_cursor, size );
		m_cursor += size;
		return true;
	}
	else
	{
		m_cursor = m_size;
		return false;
	}
}
