//
// Created by popof on 19.04.2018.
//

#ifndef BLACKENGINE_OBJECT_H
#define BLACKENGINE_OBJECT_H

#include "common/CommonHeaders.h"

#include <BlackEngine/components/ComponentsContainer.h>

#include <memory>
#include <vector>

namespace black {

class TransformComponent;

/**
 * Game entity object
 */
class BLACK_EXPORTED GameObject : public ComponentsContainer, public std::enable_shared_from_this<GameObject> {
  static long long int idCounter;

  long long int id;
  std::string name;

public:
  std::shared_ptr<TransformComponent> transform;

  /**
   * Creates an empty entity with only transform component
   */
  explicit GameObject(std::string name = "");
  virtual ~GameObject();

  const std::string &getName() const;
  void setName(const std::string &name);

  bool operator==(const GameObject &another) const noexcept;
};
}

#endif //BLACKENGINE_OBJECT_H
