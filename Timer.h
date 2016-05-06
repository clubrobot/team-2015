#ifndef TIMER_H
#define TIMER_H

#include <time.h>

class Timer
{
public:

    Timer();

    void setDuration( time_t sec, long nsec );

    void setCount( unsigned int count );

    void start();

    void stop();

    bool isOver();

private:

    struct timespec m_start;
    struct timespec m_delta;

    unsigned int m_count;

    bool m_active;
};

#endif // TIMER_H
