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
  std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
public:
  PerformanceCounter();

  /**
   * This method updates values, should be
   * called before render method
   */
  void update();

  [[nodiscard]] float getAverageMpf() const;
  [[nodiscard]] float getMinMpf() const;
  [[nodiscard]] float getMaxMpf() const;

  [[nodiscard]] float getAverageFps() const;
  [[nodiscard]] float getMinFps() const;
  [[nodiscard]] float getMaxFps() const;

  /**
   * Return a time since first update
   * @return An uptime
   */
  [[nodiscard]] long long int getUptime() const;

  [[nodiscard]] float getTimeSinceLastUpdate() const;
};
}

#endif //BLACKENGINE_PERFORMANCECOUNTER_H
