#ifndef ULTRASON_H
#define ULTRASON_H

#include <robot-robot/Module.h>

class Parasol : public Module
{
public:
    Parasol( uint8_t address, TCPClient& client );

    virtual void run();

    void initParasol();
    void openParasol();

    enum Order {INIT, OPEN};
    Order morder;

    static const uint8_t order_open, order_init;
};

#endif // ULTRASON_H
