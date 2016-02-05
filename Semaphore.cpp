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

    if(timeout > 0) res = cv.wait_for(lock, std::chrono::microseconds(timeout),[this]() { return count > 0; });
    else cv.wait(lock, [this]() { return count > 0; });

    count--;

    return res;
}
