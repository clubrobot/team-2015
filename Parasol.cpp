#include "Parasol.h"

const uint8_t Parasol::order_open = 'g';
const uint8_t Parasol::order_init = 'F';
const uint8_t Parasol::order_close = 'c';


Parasol::Parasol( uint8_t address, TCPClient& client ) : Module (address, client)
{

}

void Parasol::run()
{
	wait();

	if(morder == INIT) {
		send((uint8_t*)&order_init, 1);
	}
	if(morder == OPEN) {
		send((uint8_t*)&order_open, 1);
	}
	if(morder == CLOSE){
		send((uint8_t*)&order_close, 1);
	}
}

void Parasol::initParasol()
{
	morder = INIT;
	wakeup();
}

void Parasol::openParasol()
{
	morder = OPEN;
	wakeup();
}

void Parasol::closeParasol()
{
	morder = CLOSE;
	wakeup();
}
