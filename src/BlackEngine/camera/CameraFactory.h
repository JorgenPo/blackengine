//
// Created by popov on 08.12.2019.
//

#ifndef BLACKENGINE_CAMERAFACTORY_H
#define BLACKENGINE_CAMERAFACTORY_H

#include "Camera.h"

namespace black {

class CameraFactory {
public:
  /**
   * Create a new camera
   *
   * @param data Camera parameters
   * @return A fresh camera
   */
  [[nodiscard]] virtual std::shared_ptr<Camera> create(
    std::shared_ptr<RenderTargetInterface> renderTarget,
    std::shared_ptr<InputSystemInterface> input,
    ProjectionType projectionType,
    const glm::vec3 &position) const = 0;
};

}


#endif //BLACKENGINE_CAMERAFACTORY_H
