#include "Startup.h"

void Startup::initHardware()
{
#ifdef __arm__
    if(map_peripheral(&gpio) == -1) {
        std::cerr << "Check permission" << std::endl;
    }
    INP_GPIO(DEPART_IN);
    INP_GPIO(DEPART_OUT);
    OUT_GPIO(DEPART_OUT);

    INP_GPIO(LED_OK);
    OUT_GPIO(LED_OK);

    //
    GPIO_SET |= (1 << DEPART_OUT);
    GPIO_SET &= ~(0 << LED_OK);

    GPIO_PULL |= (1 << DEPART_IN);

#endif
}

void Startup::exitHardware()
{
#ifdef __arm__
    unmap_peripheral(&gpio);
#endif
}

bool Startup::startCondition()
{
#ifdef __arm__
    return GPIO_READ(DEPART_IN) == 0;
#else
    return false;
#endif
}

void Startup::loadingAction()
{
#ifdef __arm__
#endif
}

void Startup::readyAction()
{
#ifdef __arm__
    GPIO_SET |= (1 << LED_OK);
#endif
}
