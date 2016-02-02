/*
 * Semaphore.cpp
 *
 *  Created on: 28 janv. 2016
 *      Author: gab
 */

#include "Semaphore.h"

Semaphore::Semaphore(int count_ = 0) : count(count_) {
}

Semaphore::~Semaphore() {
}

inline void Semaphore::notify()
{
    std::unique_lock<std::mutex> lock(mtx);
    count++;
    cv.notify_one();
}

inline bool Semaphore::wait(uint timeout = 0)
{
	bool res = true;
    std::unique_lock<std::mutex> lock(mtx);

    if(timeout > 0) res = cv.wait_for(lck, std::chrono::microseconds(timeout),[this]() { return count > 0; });
    else cv.wait(lck, [this]() { return count > 0; });

    count--;

    return res;
}
