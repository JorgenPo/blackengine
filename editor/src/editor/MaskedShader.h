//
// Created by popov on 07.07.2019.
//

#ifndef BLACKENGINE_SELECTEDSHADER_H
#define BLACKENGINE_SELECTEDSHADER_H

#include <BlackEngine/shader/SimpleShader.h>

using namespace black;

namespace blackeditor {
class MaskedShader : public SimpleShader {
public:
  using SimpleShader::SimpleShader;

  void setColorMask(Color color);
};

}

#endif //BLACKENGINE_SELECTEDSHADER_H
