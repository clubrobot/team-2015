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

void EventsHandler::dispatchEvent( EventName name )
{
	m_events.push( Event( name, EventParams() ) );
}

void EventsHandler::dispatchEvent( EventName name, EventParams params )
{
	m_events.push( Event( name, params ) );
	m_sem.notify();
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
		while( m_running && pollEvent( name, params ) )
		{
			if( m_listeners.count( name ) )
			{
				EventListener listener = m_listeners[ name ];
				listener( params );
			}
		}
		m_sem.wait( 0 );
	}
}

void EventsHandler::stop( void )
{
	m_running = false;
	m_sem.notify();
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
