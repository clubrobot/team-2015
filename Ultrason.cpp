#include "Ultrason.h"

const uint8_t Ultrason::order_open = 'F';
const uint8_t Ultrason::order_init = 'F';

Ultrason::Ultrason( uint8_t address, TCPClient& client ) : Module (address, client)
{

}

void Ultrason::run()
{
    wait();

    if(morder == INIT) {
        send((uint8_t*)&order_init, 1);
    }
    else if(morder == OPEN) {
        send((uint8_t*)&order_open, 1);
    }
}

void Ultrason::initParasol()
{
    morder = INIT;
    wakeup();
}

void Ultrason::openParasol()
{
    morder = OPEN;
    wakeup();
}

