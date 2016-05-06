#ifndef STRATEGY_H
#define STRATEGY_H

#include "Ultrason.h"
#include "Startup.h"

#include <robot-robot/Brain.h>
#include <robot-robot/EventsHandler.h>

class Strategy
{
public:
    Strategy();
    virtual ~Strategy();

    void launch();

private:
    Brain mbrain;
    EventsHandler mhandler;

    void initAllModules();
    void initAllActions();
    void initStrategy();
};

#endif // STRATEGY_H
