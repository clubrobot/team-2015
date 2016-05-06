/*
 * Clock.cpp
 *
 *  Created on: 9 févr. 2016
 *      Author: ethel
 */

#include "Clock.h"

Clock::Clock() {

}

Clock::~Clock() {

}

void Clock::tic(){
    clock_gettime(CLOCK_REALTIME, &mtic);
}

double Clock::tac(){
    timespec tac;
    clock_gettime(CLOCK_REALTIME, &tac);
    return (double)(tac.tv_sec-mtic.tv_sec)+(double)(tac.tv_nsec-mtic.tv_nsec)*1e-9;
}

double Clock::utac(){
    timespec tac;
    clock_gettime(CLOCK_REALTIME, &tac);
    return (double)(tac.tv_sec-mtic.tv_sec)*1e6+(double)(tac.tv_nsec-mtic.tv_nsec)*1e-3;
}


