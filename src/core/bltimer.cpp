#include "bltimer.h"

namespace black {

Timer::Timer()
    : m_lastTime(), m_mpf(), m_fps()
{

}

void Timer::run()
{
    m_isStarted = true;
    m_startTime = Clock::now();
}

void Timer::update()
{
    if ( !m_isStarted ) {
        run();
    }

    if ( system_clock::to_time_t(m_lastTime) ) {
        double time = system_clock::to_time_t(Clock::now()) -
                system_clock::to_time_t(m_lastTime);

        // TODO: check for laggy time
        m_mpf = (time + m_mpf) / 2.0;
    }

    m_lastTime = Clock::now();
}

float Timer::mpf() const
{
    return m_mpf;
}

double Timer::uptime() const
{
    return system_clock::to_time_t(Clock::now()) -
           system_clock::to_time_t(m_startTime);
}

float Timer::fps() const
{
    return 1000.0 / mpf();
}

}
