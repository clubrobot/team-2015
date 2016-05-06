#include "Strategy.h"

Strategy::Strategy()
{
    Startup::initHardware();
    initAllModules();
    initAllActions();
    initStrategy();
}

Strategy::~Strategy()
{
    Startup::exitHardware();
}

void Strategy::launch()
{
    mhandler.run();
    mbrain.launchModules();
}

void Strategy::initAllModules()
{
    // Add all modules to the brain
}

void Strategy::initAllActions()
{
    // Add event listeners
}

void Strategy::initStrategy()
{
    Startup::readyAction();
}

