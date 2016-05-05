#include "Timer.h"

Timer::Timer()
{
    t1.tv_sec = 0;
    t2.tv_sec = 0;
    t1.tv_nsec = 0;
    t2.tv_nsec = 0;
}

bool Timer::isStopped()
{
    return t1.tv_sec == 0 && t1.tv_nsec == 0;
}

void Timer::setTime(time_t sec, long nanosec)
{
    t2.tv_sec = sec;
    t2.tv_nsec = nanosec;
}

void Timer::start()
{
    clock_gettime(CLOCK_REALTIME, &t1);
}

void Timer::stop()
{
    t1.tv_sec = 0;
    t1.tv_nsec = 0;
}

bool Timer::operator>(const Timer &t1, const struct timespec &curtime)
{
    return (t1.tv_sec + t2.tv_sec > curtime.tv_sec) &&
            (t1.tv_nsec + t2.tv_nsec > curtime.tv_nsec);
}

