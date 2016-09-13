/*
 * Semaphore.cpp
 *
 *  Created on: 28 janv. 2016
 *      Author: gab
 */

#include "Semaphore.h"

Semaphore::Semaphore(int count_) : count(count_) {
}

void Semaphore::notify()
{
    std::unique_lock<std::mutex> lock(mtx);
    count++;
    cv.notify_one();
}

bool Semaphore::wait(uint timeout)
{
	bool res = true;
    std::unique_lock<std::mutex> lock(mtx);

    if(timeout > 0) res = (cv.wait_for(lock, std::chrono::microseconds(timeout)) == std::cv_status::no_timeout);
    else cv.wait(lock);

    count--;

    return res;
}
