//
// Created by popof on 02.05.2018.
//

#ifndef BLACKENGINE_PERFORMANCECOUNTER_H
#define BLACKENGINE_PERFORMANCECOUNTER_H

#include <Exported.h>
#include <chrono>

namespace black {
    /**
     * Counts fps, mpf and min, max, average values
     */
    class BLACK_EXPORTED PerformanceCounter {
        float averageMpf;
        float minMpf;
        float maxMpf;
        float delta;

        size_t measurements;

        std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
    public:
        PerformanceCounter();

        /**
         * This method updates values, should be
         * called before render method
         */
        void update();

        float getAverageMpf() const;
        float getMinMpf() const;
        float getMaxMpf() const;

        float getAverageFps() const;
        float getMinFps() const;
        float getMaxFps() const;

        float getTimeSinceLastUpdate() const;
    };
}


#endif //BLACKENGINE_PERFORMANCECOUNTER_H
