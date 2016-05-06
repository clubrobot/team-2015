#ifndef STARTUP_H
#define STARTUP_H

// Hardware and device specific code

// Headers for Raspberry Pi
#ifdef __arm__
#include "RPI.h"
#endif

#include <iostream>

class Startup
{
public:
    static void initHardware();
    static void exitHardware();
    static bool startCondition();
    static void loadingAction();
    static void readyAction();
};

#endif // STARTUP_H
