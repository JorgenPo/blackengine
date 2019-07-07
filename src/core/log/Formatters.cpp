//
// Created by popov on 06.07.2019.
//

#include "Formatters.h"

namespace black {

std::string toString(const glm::vec3 &vec)  {
  return fmt::format("[{},{},{}]", vec.x, vec.y, vec.z);
}

}