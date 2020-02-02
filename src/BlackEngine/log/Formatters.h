//
// Created by popov on 06.07.2019.
//

#ifndef BLACKENGINE_FORMATTERS_H
#define BLACKENGINE_FORMATTERS_H

#include "../common/Color.h"

#include <glm/glm.hpp>

#include <ostream>
#include <string>

namespace glm {
template<typename Stream>
Stream &operator<<(Stream &stream, const glm::vec<3, float, glm::defaultp> &vec) {
  return stream << fmt::format("[{},{},{}]", vec.x, vec.y, vec.z);
}

template<typename Stream>
Stream &operator<<(Stream &stream, const glm::vec<4, float, glm::defaultp> &vec) {
  return stream << fmt::format("[{},{},{},{}]", vec.x, vec.y, vec.z, vec.w);
}

template<typename Stream>
Stream &operator<<(Stream &stream, const glm::vec<2, float, glm::defaultp> &vec) {
  return stream << fmt::format("[{},{}]", vec.x, vec.y);
}
}


#endif //BLACKENGINE_FORMATTERS_H
