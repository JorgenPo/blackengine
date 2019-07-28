//
// Created by popov on 06.07.2019.
//

#ifndef BLACKENGINE_FORMATTERS_H
#define BLACKENGINE_FORMATTERS_H

#include <common/Color.h>

#include <fmt/format.h>
#include <glm/glm.hpp>
#include <string>

namespace black {
std::string toString(const glm::vec4 &vec);
std::string toString(const glm::vec3 &vec);
std::string toString(const glm::vec2 &vec);
}

#endif //BLACKENGINE_FORMATTERS_H
