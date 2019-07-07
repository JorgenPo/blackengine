//
// Created by popov on 06.07.2019.
//

#include "BoundingComponent.h"

namespace black {

BoundingComponent::BoundingComponent(std::shared_ptr<BoundingShape> shape) : shape(std::move(shape)) {

}

const std::shared_ptr<BoundingShape> &BoundingComponent::getShape() const {
  return shape;
}

void BoundingComponent::setShape(std::shared_ptr<BoundingShape> newShape) {
  shape = std::move(newShape);
}

bool BoundingComponent::isIntersectsWith(const glm::vec3 &ray) {
  return shape->isIntersectsWith(ray);
}


}