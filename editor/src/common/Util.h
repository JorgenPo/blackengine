//
// Created by popov on 16.02.2020.
//

#ifndef BLACKENGINE_EDITOR_SRC_COMMON_UTIL_H
#define BLACKENGINE_EDITOR_SRC_COMMON_UTIL_H

#include <BlackEngine/input/Mouse.h>

#include <glm/vec3.hpp>
#include <QVector3D>
#include <QMouseEvent>

namespace blackeditor {

inline QVector3D toQtVector(const glm::vec3 &position) {
  return QVector3D{position.x, position.y, position.z};
}

inline glm::vec3 fromQtVector(const QVector3D &position) {
  return glm::vec3{position.x(), position.y(), position.z()};
}

std::optional<black::MouseButtonEvent> toBlackengineMouseButtonEvent(QMouseEvent *e);

std::optional<black::MouseButton> toBlackengineButton(Qt::MouseButton button);

}

#endif //BLACKENGINE_EDITOR_SRC_COMMON_UTIL_H
