/*
 * Clock.h
 *
 *  Created on: 9 févr. 2016
 *      Author: ethel
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <time.h>

#define CLOCKS_PER_US CLOCKS_PER_SEC/1000000

class Clock {
public:
	Clock();
	virtual ~Clock();

	void tic();//computes start of duration.
	double tac();//computes duration and return duration in s.
	double utac();//computes duration and return duration in s.

private:
        timespec mtic; //start of duration

};

#endif /* CLOCK_H_ */
