//
// Created by popov on 06.07.2019.
//

#include "Formatters.h"

namespace black {

std::string toString(const glm::vec3 &vec)  {
  return fmt::format("[{},{},{}]", vec.x, vec.y, vec.z);
}

std::string toString(const glm::vec4 &vec) {
  return fmt::format("[{},{},{},{}]", vec.x, vec.y, vec.z, vec.w);
}

std::string toString(const glm::vec2 &vec) {
  return fmt::format("[{},{}]", vec.x, vec.y);
}

}