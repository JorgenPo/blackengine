//
// Created by popof on 20.04.2018.
//

#ifndef BLACKENGINE_COLOR_H
#define BLACKENGINE_COLOR_H

#include <Exported.h>
#include <array>

namespace black {
class BLACK_EXPORTED Color {
public:
  float r;
  float g;
  float b;
  float a;

  explicit Color(std::array<float, 4> color) : r(color[0]), g(color[1]), b(color[2]), a(color[3]) {}
  Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

  static const std::array<float, 4> RED;
  static const std::array<float, 4> GREEN;
  static const std::array<float, 4> BLUE;
  static const std::array<float, 4> YELLOW;
  static const std::array<float, 4> WHITE;
  static const std::array<float, 4> BLACK;

  [[nodiscard]] std::array<float, 4> getArray() const;
};
}
#endif //BLACKENGINE_COLOR_H
