#ifndef STRATEGY_H
#define STRATEGY_H

#include "Parasol.h"
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

	// Modules
	Parasol mparasol;
	Ultrason multrason;
	Motor mmotor;


	void initAllModules();
	void initAllActions();
	void initStrategy();
};

#endif // STRATEGY_H
