/*
 * Message.cpp
 *
 *  Created on: 1 oct. 2015
 *      Author: ethel
 */

#include "Message.h"

Message::Message()
{
	memitter = 0;
	mdestination = 0;
	mdlc = 0;
	mdata = 0;
	mcursor = 0;
}

Message::Message( const uint8_t* rawData, uint32_t rawDlc )
{
	memitter = rawData[ 0 ];
	mdestination = rawData[ 1 ];
	setData( rawData + METADATA_LENGTH, rawDlc - METADATA_LENGTH );
	mcursor = 0;
}

Message::Message( const Message& msg )
{
	operator=( msg );
}

void Message::operator=( const Message& msg )
{
	memitter = msg.memitter;
	mdestination = msg.mdestination;
	setData( msg.mdata, msg.mdlc );
	mcursor = msg.mcursor;
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
	if ( mdata != 0 )
		delete[] mdata;

	if ( mdlc > 0 )
		mdlc = 0;
}

uint32_t Message::getDataLength() const
{
	return mdlc;
}

const uint8_t* Message::getData() const
{
	return mdata;
}

void Message::copyData( uint8_t* dst ) const
{
	if ( mdata != 0 )
		memcpy( dst, mdata, mdlc );
}

void Message::setData( const uint8_t data[], uint32_t dlc )
{
	clearData();
	mdata = new uint8_t[ dlc ];
	memcpy( mdata, data, dlc );
	mdlc = dlc;
}

void Message::appendData( const uint8_t data[], uint32_t dlc )
{
	uint32_t newDlc = mdlc + dlc;
	uint8_t* newData = new uint8_t[ newDlc ];
	memcpy( newData, mdata, mdlc );
	memcpy( newData + mdlc, data, dlc );
	clearData();
	mdlc = newDlc;
	mdata = newData;
}

uint32_t Message::getRawDataLength() const
{
	return mdlc + METADATA_LENGTH;
}

void Message::getRawData( uint8_t* dst ) const
{
	dst[ 0 ] = memitter;
	dst[ 1 ] = mdestination;
	memcpy( dst + METADATA_LENGTH, mdata, mdlc );
}
