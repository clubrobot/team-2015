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
#include <list>

#include "UntypedStack.h"
#include "Semaphore.h"
#include "Timer.h"

//

typedef std::string EventName;

typedef UntypedStack EventParams;

typedef std::pair< EventName, EventParams > Event;

typedef std::function< void( EventParams ) > EventListener;

//

class EventsHandler
{
public:

	EventsHandler();

	virtual ~EventsHandler();

	void dispatchEvent( EventName name, EventParams params = EventParams() );

	bool addEventListener( EventName name, EventListener listener );

	bool performWithDelay( double time, EventListener listener, unsigned int repeat = 1 ); // repeat = 0 means the timer will loop forever

	bool removeEventListener( EventName name );

	void run( void );

	void stop( void );

	bool isRunning( void ){ return m_running; }

protected:

	bool pollEvent( EventName& name, EventParams& params );

	//

	std::map< EventName, EventListener > m_listeners;

	std::queue< Event > m_events;

	std::list< std::pair< Timer, EventListener > > m_timers;

	bool m_running;

	Semaphore m_sem;

	friend int main( int argc, char **argv );
};

#endif /* EVENTSHANDLER_H_ */
