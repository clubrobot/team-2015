/*
 * Module.cpp
 *
 *  Created on: Nov 10, 2015
 *      Author: gabriel
 */

#include <iostream>

#include "Module.h"



Module::Module( uint8_t address, TCPClient& client )
:	maddress( address )
,	mclient( client )
,	mrunning( true )
,	mthread( nullptr )
,	mmsgs() // reserve( 256 ) is called in the constructor's body
,	mread( 0 ), mwrite( 0 )
,	msize( 0 )
,	mwaiting( false )
{
	mmsgs.reserve( 256 );
}

Module::~Module()
{
	close();
}

void Module::launch()
{
	mthread = new std::thread( &Module::threadfct, this );
}

void Module::close()
{
	if( mrunning )
	{
		mrunning = false;

		// Unlock the thread
		wakeup();

		// Wait that the thread function returns
		mthread->join();

		delete( mthread );
	}
}

void Module::wakeup()
{
	msem.notify();
}

void Module::pushData( uint8_t buffer[], uint32_t len )
{
	mmutex.lock();

	if( msize >= mmsgs.size() )
	{
		std::cout << "Module " << int( maddress ) << " : Buffer full" << std::endl;
		mmutex.unlock();
		return;
	}
	len--;

	// Prevent overflow
	len = ( len < mmsgs.size() - msize ) ? len : mmsgs.size() - msize;
	uint32_t step1 = ( len < mmsgs.size() - mwrite ) ? len : mmsgs.size() - mwrite;
	memcpy( &mmsgs[ mwrite ], buffer+1, step1 );
	if( len != step1 )
	{
		memcpy( &mmsgs[ 0 ], buffer + step1 + 1, ( len - step1 ) );
	}
	msize += len;
	mwrite = ( mwrite + len ) % mmsgs.size();

	mmutex.unlock();

}

uint8_t Module::getAddress() const
{
	return maddress;
}

bool Module::wait( uint timeout )
{
	return msem.wait( timeout );
}

bool Module::requestSlot( Message out, Message& in )
{
	return false;
	/*// Send the message
	send( out );

	// Module is now waiting for an answer
	mwaiting = true;
	if( wait( 100 ) ) // if the module is woke up by the brain
	{
		in = mmsgs.front();
		mmsgs.pop();
		mwaiting = false;
		return true;
	}
	// Timeout expired : no answer from the slot
	mwaiting = false;
	return false;*/
}

bool Module::isWaitingMsg() const
{
	return mwaiting;
}

void Module::send( uint8_t buffer[], uint32_t len )
{
	uint8_t* data = new uint8_t[ len + 2 ];
	data[ 0 ] = uint8_t( len );
	data[ 1 ] = maddress;
	memcpy( data + 2, buffer, len );
	mclient.write( data, len + 2 );
	delete( data );
}

size_t Module::getBufferSize()
{
	return msize;
}

void Module::getBufferData( uint8_t buffer[], uint32_t len )
{
	mmutex.lock();
	if( msize == 0 )
	{
		std::cout << "Module " << int( maddress ) << " : Buffer empty" << std::endl;
		mmutex.unlock();
		return;
	}

	//Prevent underflow
	len = ( msize - len > 0 ) ? len : msize;
	uint32_t step1 = ( len < mmsgs.size() - mread ) ? len : mmsgs.size() - mread;
	memcpy( buffer, &mmsgs[ mread ], step1 );
	if( len != step1 )
	{
		memcpy( buffer + step1, &mmsgs[ 0 ], len - step1 );
	}
	msize -= len;
	mread = ( mread + len ) % mmsgs.size();
	mmutex.unlock();
}

void Module::setBufferAllocSize(size_t size)
{
	mmsgs.reserve( size );
}

void Module::threadfct()
{
	while( mrunning )
	{
		this->run();
	}
}
