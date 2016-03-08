/*
 * UntypedStack.cpp
 *
 *  Created on: 8 mars 2016
 *      Author: ulysse
 */

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
		delete[] m_vector;
	}
	m_size = 0;
}
