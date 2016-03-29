/*
 * main.cpp
 *
 *  Created on: 1 oct. 2015
 *      Author: ethel
 */

#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "../EventsHandler.h"

using namespace std;

void programThreadFunction( EventsHandler* handler )
{
	while( true )
	{
		std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
		handler->dispatchEvent( "enslavementEnded", EventParams() << float( 99.0 ) << float( 0.01 ) );
		std::this_thread::sleep_for( std::chrono::seconds( 2 ) );
		handler->dispatchEvent( "enslavementEnded", EventParams() << float( -20.0 ) << float( 10.0 ) );
		std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
		handler->dispatchEvent( "enslavementEnded", EventParams() << float( 37.3 ) << float( -6.75 ) );
	}
}

void timingThreadFunction( EventsHandler* handler )
{
	std::this_thread::sleep_for( std::chrono::seconds( 6 ) );
	handler->dispatchEvent( "30secondsLeft" );
	std::this_thread::sleep_for( std::chrono::seconds( 3 ) );
	handler->dispatchEvent( "timeIsOver" );
}

void batteryThreadFunction( EventsHandler* handler )
{
	std::srand( std::time( 0 ) );
	std::this_thread::sleep_for( std::chrono::seconds( std::rand() % 20 ) );
	cout << "Battery is low" << endl;
	handler->dispatchEvent( "batteryIsLow" );
}

int main( int argc, char **argv ) {

	EventsHandler handler;

	// Démonstration du passage de paramètres au listener via la liste
	// d'arguments variable et EventsHandler::next< T >.

	EventListener destinationListener = []( EventParams params )
	{
		float x, y;
		params >> x >> y;
		cout << "Robot has reached its destination( x = " << x << ", y = " << y << " )" << endl;
	};

	// Simple listener.

	EventListener parasolListener = []( EventParams params )
	{
		cout << "Robot is opening its parasol." << endl;
	};

	// Démonstration du concept de closure : si handler n'avait pas été passé
	// au listener via les crochets, il n'aurait pas été accessible depuis
	// l'intérieur de celui-ci.

	EventListener turnOffListener = [ &handler ]( EventParams params )
	{
		handler.stop();
	};

	// Configuration des différents events et de leurs listeners associés.
	// Les threads sont ici juste pour simuler le fonctionnement des différents
	// modules.

	handler.addEventListener( "enslavementEnded",	destinationListener	);
	handler.addEventListener( "30secondsLeft",		parasolListener		);
	handler.addEventListener( "timeIsOver",			turnOffListener		);
	handler.addEventListener( "batteryIsLow",		turnOffListener		);

	std::thread programThread( programThreadFunction, &handler );
	std::thread timingThread( timingThreadFunction, &handler );
	std::thread batteryThread( batteryThreadFunction, &handler );

	// Main loop

	handler.run();

	// Happy :)

	cout << "Program ended. Congratulations !" << endl;

	programThread.join();
	timingThread.join();
	batteryThread.join();

	return 0;
}



