//
// Created by popof on 02.05.2018.
//

#include "PerformanceCounter.h"
#include <algorithm>
#include <log/Logger.h>

namespace black {
    PerformanceCounter::PerformanceCounter()
        : minMpf(10000), maxMpf(0.0f), averageMpf(0.0f), measurements(0), delta(0.0f)
    {
    }

    void PerformanceCounter::update() {
        static bool firstTime = true;

        if (firstTime) {
            this->lastTime = std::chrono::high_resolution_clock::now();
            this->startTime = std::chrono::high_resolution_clock::now();
        }

        auto now = std::chrono::high_resolution_clock::now();

        long long int millisecondsPassed = std::chrono::duration_cast<std::chrono::milliseconds>
                (now - lastTime).count();

        this->lastTime = now;

        if (!firstTime) {
            this->delta = static_cast<float>(millisecondsPassed);
            this->minMpf = std::min(this->minMpf, static_cast<float>(millisecondsPassed));
            this->maxMpf = std::max(this->maxMpf, static_cast<float>(millisecondsPassed));
            this->averageMpf = (this->averageMpf * this->measurements + millisecondsPassed) / (this->measurements + 1);
            this->measurements++;
        }

        if (firstTime) {
            firstTime = false;
        }
    }

    float PerformanceCounter::getAverageMpf() const {
        return this->averageMpf;
    }

    float PerformanceCounter::getMinMpf() const {
        return this->minMpf;
    }

    float PerformanceCounter::getAverageFps() const {
        return 1000.0f / this->averageMpf;
    }

    float PerformanceCounter::getMinFps() const {
        return 1000.0f / this->maxMpf;
    }

    float PerformanceCounter::getMaxFps() const {
        return 1000.0f / this->minMpf;
    }

    float PerformanceCounter::getMaxMpf() const {
        return this->maxMpf;
    }

    float PerformanceCounter::getTimeSinceLastUpdate() const {
        return this->delta;
    }

    long long int PerformanceCounter::getUptime() const {
        auto now = std::chrono::high_resolution_clock::now();

        return std::chrono::duration_cast<std::chrono::milliseconds>
                (now - this->startTime).count();
    }
}
