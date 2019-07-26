//
// Created by popof on 25.04.2018.
//

#ifndef BLACKENGINE_GLTEXTURE_H
#define BLACKENGINE_GLTEXTURE_H

#include "OpenGLCommonHeaders.h"
#include <common/CommonHeaders.h>
#include <render/Texture.h>

namespace black {
class GLTexture : public Texture {
  GLuint texture;

public:
  explicit GLTexture(const std::shared_ptr<Image> &image, bool generateMipMaps = true,
                     TextureFiltering filtering = TextureFiltering::NEAREST,
                     TextureWrapping wrapping = TextureWrapping::CLAMP_TO_BORDER);

private:
  void bind() override;
  void unbind() override;
};
}

#endif //BLACKENGINE_GLTEXTURE_H
