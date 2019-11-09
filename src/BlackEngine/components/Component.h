//
// Created by popof on 23.04.2018.
//

#ifndef BLACKENGINE_COMPONENT_H
#define BLACKENGINE_COMPONENT_H

namespace black {
/**
 * A component for a game object
 */
class Component {

public:
  // Making Component polymorphic
  virtual ~Component() = default;
};

}

#endif //BLACKENGINE_COMPONENT_H
