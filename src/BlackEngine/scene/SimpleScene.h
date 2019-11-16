//
// Created by popov on 09.07.2019.
//

#ifndef BLACKENGINE_SIMPLESCENE_H
#define BLACKENGINE_SIMPLESCENE_H

#include "AbstractScene.h"

namespace black {

/**
 * Simple vector based scene implementation
 */
class BLACK_EXPORTED SimpleScene : public AbstractScene {
  std::vector<std::shared_ptr<GameObject>> objects;
  std::shared_ptr<Light> light;
  std::string sceneName;

public:
  explicit SimpleScene(std::string_view name);

  void addObject(std::shared_ptr<GameObject> object) override;

  void addObjects(const std::vector<std::shared_ptr<GameObject>> &objects) override;

  void removeObject(std::string_view name) override;

  [[nodiscard]] std::shared_ptr<GameObject> getObject(std::string_view name) const override;

  [[nodiscard]] const std::vector<std::shared_ptr<GameObject>> &getObjects() const override;

  [[nodiscard]] bool hasObject(std::string_view name) const override;

  [[nodiscard]] std::string_view getName() const override;

  [[nodiscard]] bool hasLight() const override;

  [[nodiscard]] std::shared_ptr<Light> getLight() const override;

private:
  [[nodiscard]] std::vector<std::shared_ptr<GameObject>>::const_iterator getObjectIterator(std::string_view name) const;
};

}


#endif //BLACKENGINE_SIMPLESCENE_H
