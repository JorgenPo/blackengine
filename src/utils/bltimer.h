#ifndef BLTIMER_H
#define BLTIMER_H

#include <chrono>

using namespace std::chrono;

namespace black {

/**
 * @brief The Timer class.
 *  Counts milliseconds per frame to
 * compute fps and other metrics for the application.
 * Based on std::chrono gives awesome perfomance and
 * presice to you!
 *
 * @author george popoff <popoff96@live.com>
 * @date 11.03.2017
 *
 * @version 1.0 Fully working class.
 *
 */
class Timer {
    using Clock = high_resolution_clock;
    using Time = high_resolution_clock::time_point;
    using Duration = milliseconds;

public:
    Timer();

    void run();
    void tick();

    // Getters
    float fps() const;
    float mpf() const;

    double uptime() const;

private:
    double m_tickCount;
    bool m_isStarted = false;

    Time m_startTime;
    Time m_lastTime;
    Duration m_mpf;
    float m_fps;
};

} // end of black namespace
#endif // BLTIMER_H
