//
// Created by popof on 28.10.2018.
//

#ifndef BLACKENGINE_MATERIAL_H
#define BLACKENGINE_MATERIAL_H

#include <CommonHeaders.h>
#include <Color.h>

#include <memory>

namespace black {
class Texture;

/**
 * Some shader information about concrete material.
 */
struct BLACK_EXPORTED Material {
  std::shared_ptr<Texture> texture;
  Color color;

  explicit Material(std::shared_ptr<Texture> texture);
  explicit Material(Color color);
  Material();
};

}

#endif //BLACKENGINE_MATERIAL_H
