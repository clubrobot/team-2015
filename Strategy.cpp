#include "Strategy.h"

Strategy::Strategy()
: mparasol(1, mbrain), multrason(2, mbrain), mmotor(3, mbrain)
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
    mbrain.addModule(&mparasol);

}

void Strategy::initAllActions()
{
	// Add event listeners

	mhandler.addEventListener("chrono90" ,[this](EventParams params) {
		this->mparasol.openParasol();
	});

	mhandler.addEventListener("chronoFin", [this](EventParams params) {
		this->mparasol.closeParasol();
	});

	mhandler.addEventListener("data", [this](EventParams params){
		uint8_t id, length;
		params >> id >> length;
		if(length < 3){
			this->mmotor.stop();
		}
	});

}

void Strategy::initStrategy()
{
    while(!Startup::startCondition());
    std::cout << "Open parasol" << std::endl;
    mparasol.openParasol();

}

