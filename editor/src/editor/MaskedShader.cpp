//
// Created by popov on 07.07.2019.
//

#include "MaskedShader.h"
#include <BlackEngine/log/Logger.h>

using namespace blackeditor;

void MaskedShader::setColorMask(Color color) {
  this->impl->setUniformVariable("colorMask", color.getRgb());
}
