//
// Created by popof on 20.04.2018.
//

#include "Color.h"

namespace black {

Color::Color(std::array<float, 4> color) : r(color[0]), g(color[1]), b(color[2]), a(color[3]) {}

Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

Color::Color(std::array<float, 3> color) : Color(std::array<float, 4>{color[0], color[1], color[2], 1.0f}) {
}

const Color   Color::RED = {1.0f, 0.0f, 0.0f, 1.0f};
const Color   Color::GREEN = {0.0f, 1.0f, 0.0f, 1.0f};
const Color   Color::BLUE = {0.0f, 0.0f, 1.0f, 1.0f};
const Color   Color::YELLOW = {1.0f, 0.8f, 0.1f, 1.0f};
const Color   Color::WHITE = {1.0f, 1.0f, 1.0f, 1.0f};
const Color   Color::BLACK = {0.0f, 0.0f, 0.0f, 1.0f};

std::array<float, 3> Color::getRgb() const {
  return {r, g, b};
}

std::array<float, 4> Color::getRgba() const {
  return {r, g, b, a};
}
}
