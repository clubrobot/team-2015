/*
 * Message.cpp
 *
 *  Created on: 1 oct. 2015
 *      Author: ethel
 */

#include <cstring>

#include "Message.h"

Message::Message()
{
	memitter = 0;
	mdestination = 0;
}

Message::Message( const uint8_t* rawData, uint32_t rawDlc )
{
	memitter = rawData[ 0 ];
	mdestination = rawData[ 1 ];
	setData( ( uint8_t* ) ( rawData + METADATA_LENGTH ), rawDlc - METADATA_LENGTH );
}

Message::Message( const Message& msg )
{
	operator=( msg );
}

void Message::operator=( const Message& msg )
{
	memitter = msg.memitter;
	mdestination = msg.mdestination;
	setData( getData(), getDataLength() );
}

Message::~Message()
{
	clearData();
}

uint8_t Message::getEmitter() const
{
	return memitter;
}

void Message::setEmitter( uint8_t emitter )
{
	memitter = emitter;
}

uint8_t Message::getReceiver() const
{
	return mdestination;
}

void Message::setReceiver( uint8_t destination )
{
	mdestination = destination;
}

void Message::clearData()
{
	clear();
}

uint32_t Message::getDataLength() const
{
	return m_size;
}

const uint8_t* Message::getData() const
{
	return ( uint8_t* ) m_vector;
}

void Message::copyData( uint8_t* dst ) const
{
	if ( !empty() )
	{
		memcpy( dst, getData(), getDataLength() );
	}
}

void Message::setData( const uint8_t data[], uint32_t dlc )
{
	clearData();
	binary_push( data, dlc );
}

void Message::appendData( const uint8_t data[], uint32_t dlc )
{
	binary_push( data, dlc );
}

uint32_t Message::getRawDataLength() const
{
	return getDataLength() + METADATA_LENGTH;
}

void Message::getRawData( uint8_t* dst ) const
{
	dst[ 0 ] = memitter;
	dst[ 1 ] = mdestination;
	memcpy( dst + METADATA_LENGTH, getData(), getDataLength() );
}
