/*
 * Message.h
 *
 *  Created on: 1 oct. 2015
 *      Author: ethel
 *
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <stdint.h>
#include <cstring>
#include <vector>

// The size of a raw message while excluding the size of its data. For instance it's the size needed to store the emitter's id.
#define METADATA_LENGTH 2

class Message {

protected:

	uint8_t memitter; // The emitter's id.
	uint8_t mdestination; // The receiver's id.
	uint32_t mdlc; // The length of the internal data.
	uint8_t* mdata; // The internal data.
<<<<<<< Upstream, based on branch 'master' of https://github.com/IR-RC/arietta-robot.git
	uint8_t mcursor; // The position in the data where to retrieve the current variable. See append and retrieve methods.
=======
	mutable uint8_t mcursor; // The position in the data where to retrieve the current variable. See append and retrieve methods.
>>>>>>> 4ac70c5 Message Refactoring

public:

	// Create an empty message.
	Message();

	// Build a message from its raw data.
	Message( const uint8_t* rawData, uint32_t rawDlc );

	// Virtual destructor.
	virtual ~Message();

	// Get the message's emitter.
<<<<<<< Upstream, based on branch 'master' of https://github.com/IR-RC/arietta-robot.git
	uint8_t getEmitter();
=======
	uint8_t getEmitter() const;
>>>>>>> 4ac70c5 Message Refactoring

	// Set the message's emitter.
	void setEmitter( uint8_t emitter );

	// Get the message's receiver.
<<<<<<< Upstream, based on branch 'master' of https://github.com/IR-RC/arietta-robot.git
	uint8_t getReceiver();

	// Set the receiver.
	void setReceiver( uint8_t destination );

	// Clear the message's data. This can't be undone.
	void clearData();

	// Get the length of the message's data.
	uint32_t getDataLength();

	// Copy the message's data to another memory location, assuming it has previously been allocated (using getDataLength).
	void getData( uint8_t* dst );

	// Set the message's data by erasing the previous one.
	void setData( const uint8_t data[], uint32_t dlc );

	// Add some new data to the message's one.
	void appendData( const uint8_t data[], uint32_t dlc );

	// Get the length of the message's entire data. This includes metadata like the message's emitter or receiver.
	uint32_t getRawDataLength();

	// Get the message's raw data (see above).
	void getRawData( uint8_t* dst );
=======
	uint8_t getReceiver() const;

	// Set the receiver.
	void setReceiver( uint8_t destination );

	// Clear the message's data. This can't be undone.
	void clearData();

	// Get the length of the message's data.
	uint32_t getDataLength() const;

	// Copy the message's data to another memory location, assuming it has previously been allocated (using getDataLength).
	void getData( uint8_t* dst ) const;

	// Set the message's data by erasing the previous one.
	void setData( const uint8_t data[], uint32_t dlc );

	// Add some new data to the message's one.
	void appendData( const uint8_t data[], uint32_t dlc );

	// Get the length of the message's entire data. This includes metadata like the message's emitter or receiver.
	uint32_t getRawDataLength() const;

	// Get the message's raw data (see above).
	void getRawData( uint8_t* dst ) const;
>>>>>>> 4ac70c5 Message Refactoring

	// Add a new formatted variable to the message. For example :
	//
	// float pi = 3.14;
	// Message m();
	// m.append< float >( pi );

	template< typename T >
	void append( T data )
	{
		appendData( ( const uint8_t* ) &data, sizeof( T ) );
	}

	// Get a formatted variable from the message.
	// Notice that there is an internal cursor which is incremented every time a variable is retrieved.
	// For example :
	//
	// int a, b;
	// float c;
	// Message m( receivedRawData ); // The cursor is at position zero.
	// a = m.retrieve< int >(); // The cursor is incremented by sizeof( int ).
	// b = m.retrieve< int >(); // Idem.
	// c = m.retrieve< float >();

	template< typename T >
<<<<<<< Upstream, based on branch 'master' of https://github.com/IR-RC/arietta-robot.git
	T retrieve( void )
=======
	T retrieve( void ) const
>>>>>>> 4ac70c5 Message Refactoring
	{
		T var;
		memcpy( &var, mdata + mcursor, sizeof( T ) );
		mcursor += sizeof( T );
		return var;
	}
};

#endif /* MESSAGE_H_ */
