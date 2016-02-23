/*
 * Clock.cpp
 *
 *  Created on: 9 févr. 2016
 *      Author: ethel
 */

#include "Clock.h"

Clock::Clock(): mtic(0){

}

Clock::~Clock() {

}

void Clock::tic(){
	mtic =clock();
}

double Clock::tac(){
	return (clock()-mtic)/(double)(CLOCKS_PER_SEC);//
}

double Clock::utac(){
	return (clock()-mtic)/(double)(CLOCKS_PER_US);//
}


