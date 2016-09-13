#include "Timer.h"

#include <iostream>

Timer::Timer()
{
	m_start.tv_sec = 0;
	m_start.tv_nsec = 0;
	m_delta.tv_sec = 0;
	m_delta.tv_nsec = 0;
	m_count = 0;
	m_active = false;
}

void Timer::setDuration( time_t sec, long nsec )
{
	m_delta.tv_sec = sec;
	m_delta.tv_nsec = nsec;
}

void Timer::setCount( unsigned int count )
{
	m_count = count;
}

void Timer::start()
{
	clock_gettime( CLOCK_REALTIME, &m_start );
	m_active = true;
}

void Timer::stop()
{
	if( m_active )
	{
		struct timespec curtime;
		clock_gettime( CLOCK_REALTIME, &curtime );
		m_delta.tv_sec -= curtime.tv_sec - m_start.tv_sec;
		m_delta.tv_nsec -= curtime.tv_nsec - m_start.tv_nsec;
	}
	m_active = false;
}

bool Timer::isOver()
{
	struct timespec curtime;
	clock_gettime( CLOCK_REALTIME, &curtime );
	if( m_active && curtime.tv_sec >= m_start.tv_sec + m_delta.tv_sec && curtime.tv_nsec >= m_start.tv_nsec + m_delta.tv_nsec )
	{
		m_start.tv_sec += m_delta.tv_sec;
		m_start.tv_nsec += m_delta.tv_nsec;
		if( m_count-- > 0 && m_count == 0 )
		{
			m_active = false;
		}
		return true;
	}
	return false;
}

