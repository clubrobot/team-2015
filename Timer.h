#ifndef TIMER_H
#define TIMER_H

#include <time.h>

class Timer
{
public:
    Timer();

    bool isStopped();

    void setTime(time_t sec, long nanosec);

    void start();

    void stop();

    friend bool operator>(const Timer &t1, const struct timespec &curtime);

    struct timespec t1, t2;
    std::string eventName;
};

#endif // TIMER_H
