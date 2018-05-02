//
// Created by popof on 02.05.2018.
//

#include "PerformanceCounter.h"
#include <chrono>
#include <algorithm>
#include <core/Logger.h>

namespace black::performance {
    PerformanceCounter::PerformanceCounter()
        : minMpf(10000), maxMpf(-0.0f), averageMpf(0.0f), measurements(0)
    {
        this->lastTime = std::chrono::high_resolution_clock::now();
    }

    void PerformanceCounter::update() {
        auto now = std::chrono::high_resolution_clock::now();

        long long int millisecondsPassed = std::chrono::duration_cast<std::chrono::milliseconds>
                (now - lastTime).count();

        this->lastTime = now;

        this->minMpf = std::min(this->minMpf, static_cast<float>(millisecondsPassed));
        this->maxMpf = std::max(this->maxMpf, static_cast<float>(millisecondsPassed));

        Logger::info("Passed = %v", millisecondsPassed);

        this->averageMpf = (this->averageMpf * this->measurements + millisecondsPassed) / (this->measurements + 1);

        this->measurements++;
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
}
