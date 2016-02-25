/*
 * EventsHandler.cpp
 *
 *  Created on: 25 févr. 2016
 *      Author: ulysse
 */

#include <chrono>
#include <thread>

#include "EventsHandler.h"

EventsHandler::EventsHandler()
:	m_running( false )
{

}

EventsHandler::~EventsHandler()
{

}

void EventsHandler::dispatchEvent( EventName name, ... )
{
	EventParams params = static_cast< EventParams >( ( &name ) + 1 );
	m_events.push( Event( name, params ) );
}

bool EventsHandler::addEventListener( EventName name, EventListener listener )
{
	m_listeners[ name ] = listener; // Erase previous listener
	return true;
}

bool EventsHandler::removeEventListener( EventName name )
{
	if( m_listeners.count( name ) )
	{
		m_listeners.erase( name );
		return true;
	}
	return false;
}

void EventsHandler::run( void )
{
	m_running = true;
	while( m_running )
	{
		EventName name;
		EventParams params;
		while( pollEvent( name, params ) )
		{
			if( m_listeners.count( name ) )
			{
				EventListener listener = m_listeners[ name ];
				listener( params );
			}
		}
		std::this_thread::sleep_for( std::chrono::milliseconds( 16 ) ); // Sleep for a while...
	};
}

void EventsHandler::stop( void )
{
	m_running = false;
}

bool EventsHandler::pollEvent( EventName& name, EventParams& params )
{
	if( !m_events.empty() )
	{
		Event event = m_events.front();
		name = event.first;
		params = event.second;
		m_events.pop();
		return true;
	}
	return false;
}
