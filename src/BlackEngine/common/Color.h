//
// Created by popof on 20.04.2018.
//

#ifndef BLACKENGINE_COLOR_H
#define BLACKENGINE_COLOR_H

#include "Exported.h"

#include <fmt/format.h>
#include <array>

namespace black {
class BLACK_EXPORTED Color {
public:
  float r;
  float g;
  float b;
  float a;

  explicit Color(std::array<float, 4> color);
  explicit Color(std::array<float, 3> color);
  Color(float r, float g, float b, float a = 1.0f);


  static const Color RED;
  static const Color GREEN;
  static const Color BLUE;
  static const Color YELLOW;
  static const Color WHITE;
  static const Color BLACK;
  static const Color GRAY;

  [[nodiscard]] std::array<float, 3> getRgb() const;
  [[nodiscard]] std::array<float, 4> getRgba() const;
};
}

template<>
struct fmt::formatter<black::Color> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }

  template <typename FormatContext>
  auto format(const black::Color &c, FormatContext &ctx) {
    return format_to(ctx.out(), "Color({},{},{},{})", c.r, c.g, c.b, c.a);
  }
};

#endif //BLACKENGINE_COLOR_H
