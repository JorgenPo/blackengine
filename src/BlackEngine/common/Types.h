//
// Created by popof on 26.09.2018.
//

#ifndef BLACKENGINE_TYPES_H
#define BLACKENGINE_TYPES_H

#include "Exported.h"
#include "Config.h"
#include <glm/vec3.hpp>
#include <fmt/format.h>
#include <glm/vec2.hpp>

#if defined(BLACK_PLATFORM_WINDOWS)
#include <plugins/windows/WindowsSharedLibrary.h>
#elif defined(BLACK_PLATFORM_LINUX)
#include "../plugins/linux/LinuxSharedLibrary.h"

#endif

namespace black {
#ifdef BLACK_PLATFORM_WINDOWS
using SharedLibrary = os::WindowsSharedLibrary;
#elif defined(BLACK_PLATFORM_LINUX)
using SharedLibrary = os::LinuxSharedLibrary;
#elif defined(BLACK_PLATFORM_MACOSX)
using SharedLibrary = os::MacOSSharedLibrary;
#endif

/**
 * Renderer Draw mode
 */
enum class DrawMode {
  POINTS,
  LINES,
  LINE_LOOP,
  LINE_STRIP,
  TRIANGLE_STRIP,
  TRIANGLE_FAN,
  TRIANGLES,
  QUAD_STRIP,
  QUADS,
  POLYGON
};

using Vector3D = glm::vec3;
using Vector2D = glm::vec2;
using Point2D = glm::vec2;
using Point3D = glm::vec3;

}

#endif //BLACKENGINE_TYPES_H
