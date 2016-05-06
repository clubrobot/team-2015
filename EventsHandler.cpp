/*
 * EventsHandler.cpp
 *
 *  Created on: 25 févr. 2016
 *      Author: ulysse
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

#include "EventsHandler.h"

EventsHandler::EventsHandler()
:	m_running( false )
{

}

EventsHandler::~EventsHandler()
{

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

bool EventsHandler::performWithDelay( double time, EventListener listener, unsigned int repeat )
{
	Timer timer;
	double sec, nsec;
	nsec = modf( time, &sec );
	timer.setDuration( (time_t)sec, (long)(nsec * 1e9) );
	timer.setCount( repeat );
	timer.start();
	m_timers.push_back( std::pair< Timer, EventListener >( timer, listener ) );
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
		for( auto it = m_timers.begin(); it != m_timers.end(); it++ )
		{
		    Timer& timer = it->first;
		    EventListener& listener = it->second;
		    if( timer.isOver() )
		    {
		    	listener( EventParams() );
		    }
		}

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
		m_sem.wait( 100 );	// Wait 100 ms before executing the new cycle
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
