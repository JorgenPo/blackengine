//
// Created by popof on 20.04.2018.
//

#include "Color.h"

namespace black {
    const std::array<float, 4>   Color::RED =       {1.0f, 0.0f, 0.0f, 1.0f};
    const std::array<float, 4>   Color::GREEN =     {0.0f, 1.0f, 0.0f, 1.0f};
    const std::array<float, 4>   Color::BLUE =      {0.0f, 0.0f, 1.0f, 1.0f};
    const std::array<float, 4>   Color::YELLOW =    {0.0f, 1.0f, 1.0f, 1.0f};
    const std::array<float, 4>   Color::WHITE =     {1.0f, 1.0f, 1.0f, 1.0f};
    const std::array<float, 4>   Color::BLACK =     {0.0f, 0.0f, 0.0f, 1.0f};

    std::array<float, 4> Color::getArray() const {
        return {r, g, b, a};
    }
}
