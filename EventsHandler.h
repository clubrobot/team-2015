/*
 * EventsHandler.h
 *
 *  Created on: 25 févr. 2016
 *      Author: ulysse
 */

#ifndef EVENTSHANDLER_H_
#define EVENTSHANDLER_H_

#include <string>
#include <utility>
#include <functional>

#include <map>
#include <queue>

//

typedef std::string EventName;

typedef void* EventParams;

typedef std::pair< EventName, EventParams > Event;

typedef std::function< void( EventParams ) > EventListener;

//

class EventsHandler
{
public:

	EventsHandler();

	virtual ~EventsHandler();

	void dispatchEvent( EventName name, ... );

	bool addEventListener( EventName name, EventListener listener );

	bool removeEventListener( EventName name );

	void run( void );

	void stop( void );

	bool isRunning( void ){ return m_running; }

	template< typename T >
	static T next( EventParams& params )
	{
		T element = *static_cast< T* >( params );
		params = static_cast< EventParams >( ( &element ) + 1 );
		return element;
	}

protected:

	bool pollEvent( EventName& name, EventParams& params );

	//

	std::map< EventName, EventListener > m_listeners;

	std::queue< Event > m_events;

	bool m_running;

	friend int main( int argc, char **argv );
};

#endif /* EVENTSHANDLER_H_ */
