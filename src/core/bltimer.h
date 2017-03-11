#ifndef BLTIMER_H
#define BLTIMER_H

#include <chrono>

using namespace std::chrono;

namespace black {

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
