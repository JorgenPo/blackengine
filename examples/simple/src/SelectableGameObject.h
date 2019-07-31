//
// Created by popov on 31.07.2019.
//

#ifndef BLACKENGINE_SELECTABLEGAMEOBJECT_H
#define BLACKENGINE_SELECTABLEGAMEOBJECT_H

#include <memory>

#include <GameObject.h>
#include <shader/ApplicationShader.h>
#include <components/ModelComponent.h>

using namespace black;

class SelectableGameObject {
  std::shared_ptr<GameObject> object;
  std::shared_ptr<ApplicationShader> selectedShader;
  std::shared_ptr<ApplicationShader> hoveredShader;
  bool isSelected = false;

public:
  SelectableGameObject() = default;

  explicit SelectableGameObject(
    std::shared_ptr<ApplicationShader> hoveredShader,
    std::shared_ptr<ApplicationShader> selectedShader)
    : selectedShader(std::move(selectedShader)), hoveredShader(std::move(hoveredShader)) {}

  void setObject(std::shared_ptr<GameObject> newObject) {
    if (object && object->getName() == newObject->getName()) {
      return;
    }

    resetObject();
    object = std::move(newObject);

    object->get<ModelComponent>()->setShader(hoveredShader);
  }

  void resetObject() {
    if (object) {
      object->get<ModelComponent>()->setShader(nullptr);
    }

    object = nullptr;
    isSelected = false;
  }

  [[nodiscard]] std::shared_ptr<GameObject> getObject() const {
    return object;
  }

  void select() {
    if (object) {
      object->get<ModelComponent>()->setShader(selectedShader);
    }
    isSelected = true;
  }

  [[nodiscard]] bool isObjectSelected() const {
    return isSelected;
  }

  void unselect() {
    if (object) {
      object->get<ModelComponent>()->setShader(nullptr);
    }
    isSelected = false;
  }
};

#endif //BLACKENGINE_SELECTABLEGAMEOBJECT_H
