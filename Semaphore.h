/*
 * Semaphore.h
 *
 *  Created on: 28 janv. 2016
 *      Author: gab
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    Semaphore (int count_ = 0);

    inline void notify();

    inline bool wait(uint timeout = 0);

private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;
};

#endif /* SEMAPHORE_H_ */
