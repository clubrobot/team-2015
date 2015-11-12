/*
 * Message.h
 *
 *  Created on: 1 oct. 2015
 *      Author: ethel
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <stdint.h>
#include <cstring>
#include <arietta-comlib/Serial/UARTServer.h>
#include <vector>

// size of raw data minus mdata
#define METADATA_LENGTH 2

class Message {
protected:

	uint8_t memitter; // emitter id
	uint8_t mdestination; // receiver id
	uint32_t mdlc; // dlc = data length code
	uint8_t* mdata;
	uint8_t mcursor; // to read data in a FILE* style

public:

	// build an empty message to send
	Message();

	// build a message from raw data received
	Message( const uint8_t* rawData, uint32_t rawDlc );

	// destructor
	virtual ~Message();

	// erase data
	void clearData();

	// get dlc
	uint32_t getDataLength();

	// copy data from the message to dst (should be allocated before!)
	void getData( uint8_t* dst );

	// set data, erase previous data
	void setData( const uint8_t data[], uint32_t dlc );

	// add data to previous one
	void appendData( const uint8_t data[], uint32_t dlc );

	// size of the entire data of the message, including metadata like emitter
	uint32_t getRawDataSize();

	// get the entire data from the message (see above)
	void getRawData( uint8_t* dst );

	// put a new formatted variable at the end of data
	template< typename T >
	void append< T >( T data )
	{
		appendData( &data, sizeof( T ) );
	}

	// get a formatted variable from data at cursor
	// cursor is incremented every call
	template< typename T >
	T retrieve< T >( void )
	{
		T var;
		memcpy( &var, mdata + mcursor, sizeof( T ) );
		mcursor += sizeof( T );
		return var;
	}
};

#endif /* MESSAGE_H_ */
