#include "bltimer.h"

namespace black {

Timer::Timer()
    : m_tickCount(), m_lastTime(), m_mpf(), m_fps()
{

}

void Timer::run()
{
    m_isStarted = true;
    m_startTime = Clock::now();
}

void Timer::tick()
{
    ++m_tickCount;

    if ( !m_isStarted ) {
        run();
    }

    if ( system_clock::to_time_t(m_lastTime) ) {
        Duration time = duration_cast<milliseconds>(Clock::now() - m_lastTime);

        m_mpf = time;
    }

    m_lastTime = Clock::now();
}

float Timer::mpf() const
{
    return m_mpf.count();
}

double Timer::uptime() const
{
    return duration_cast<milliseconds>(
                Clock::now() - m_startTime).count();
}

float Timer::fps() const
{
    return 1000.0f / static_cast<float>(m_mpf.count());
}

}
