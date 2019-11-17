//
// Created by popov on 09.07.2019.
//

#ifndef BLACKENGINE_ABSTRACTSCENE_H
#define BLACKENGINE_ABSTRACTSCENE_H

#include "../common/CommonHeaders.h"
#include <BlackEngine/common/Color.h>
#include <BlackEngine/components/LightComponent.h>

#include <memory>
#include <vector>

namespace black {
class GameObject;
class Camera;

class BLACK_EXPORTED AbstractScene {
  std::shared_ptr<Camera> currentCamera;
  AmbientLight ambientLight;

public:
  virtual ~AbstractScene();
  virtual void addObject(std::shared_ptr<GameObject> object) = 0;

  virtual void addObjects(const std::vector<std::shared_ptr<GameObject>> &objects) = 0;

  virtual void setCurrentCamera(std::shared_ptr<Camera> newCamera);

  virtual void removeObject(std::string_view name) = 0;

  [[nodiscard]] virtual std::string_view getName() const = 0;
  [[nodiscard]] virtual std::shared_ptr<GameObject> getObject(std::string_view name) const = 0;

  [[nodiscard]] virtual const std::vector<std::shared_ptr<GameObject>> &getObjects() const = 0;

  [[nodiscard]] virtual std::shared_ptr<Camera> getCurrentCamera() const;

  [[nodiscard]] virtual bool hasObject(std::string_view name) const = 0;

  [[nodiscard]] virtual bool hasLight() const = 0;
  [[nodiscard]] virtual std::shared_ptr<LightComponent> getLight() const = 0;

  virtual void setAmbientLight(AmbientLight light);
  [[nodiscard]] virtual const AmbientLight &getAmbientLight() const noexcept;
};

}

#endif //BLACKENGINE_ABSTRACTSCENE_H
