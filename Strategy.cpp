#include "Strategy.h"

Strategy::Strategy()
    : multrason(1, mbrain)
{
    Startup::initHardware();
    initAllModules();
    initAllActions();
}

Strategy::~Strategy()
{
    Startup::exitHardware();
}

void Strategy::launch()
{
    mbrain.launchModules();
    initStrategy();
    mhandler.run();
}

void Strategy::initAllModules()
{
    // Add all modules to the brain
    mbrain.addModule(&multrason);
}

void Strategy::initAllActions()
{
    // Add event listeners
}

void Strategy::initStrategy()
{
    Startup::readyAction();

    while(!Startup::startCondition());
    std::cout << "Open parasol" << std::endl;
    multrason.openParasol();
}

