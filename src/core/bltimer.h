#ifndef BLTIMER_H
#define BLTIMER_H

#include <chrono>

using namespace std::chrono;

namespace black {

class Timer {
    typedef high_resolution_clock Clock;
    typedef system_clock::time_point Time;

public:
    Timer();

    void run();
    void update();

    // Getters
    float fps() const;
    float mpf() const;

    double uptime() const;

private:
    bool m_isStarted = false;

    Time m_startTime;
    Time m_lastTime;
    double m_mpf;
    float m_fps;
};

} // end of black namespace
#endif // BLTIMER_H
