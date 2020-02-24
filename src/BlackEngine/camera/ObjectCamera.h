//
// Created by popov on 24.02.2020.
//

#ifndef BLACKENGINE_SRC_BLACKENGINE_CAMERA_OBJECTCAMERA_H
#define BLACKENGINE_SRC_BLACKENGINE_CAMERA_OBJECTCAMERA_H

#include "Camera.h"
#include "CameraFactory.h"

namespace black {

class GameObject;

/**
 * Camera focusing on an object
 */
class ObjectCamera : public Camera {
  std::shared_ptr<GameObject> object;

  float height = 5.0f; // Height above the object
  float distance = 5.0f; // Z distance to the object

public:
  class Factory : public CameraFactory {
  public:
    static constexpr const char *GetName() {
      return "ObjectCamera";
    }

    [[nodiscard]] std::shared_ptr<Camera> create(const CameraData &data) const override;
  };

  explicit ObjectCamera(const CameraData &Data);

  void update() override;

  void setObject(std::shared_ptr<GameObject> object);
  std::shared_ptr<GameObject> getObject() const;
  void resetObject();

  float getHeight() const;
  void setHeight(float height);
  float getDistance() const;
  void setDistance(float distance);
};

}

#endif //BLACKENGINE_SRC_BLACKENGINE_CAMERA_OBJECTCAMERA_H
