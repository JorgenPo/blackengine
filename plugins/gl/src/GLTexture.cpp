//
// Created by popof on 25.04.2018.
//

#include "GLTexture.h"

#include <BlackEngine/Image.h>

namespace black {

int getGLWrappingType(TextureWrapping wrapping) {
  switch (wrapping) {
  case TextureWrapping::CLAMP_TO_BORDER:return GL_CLAMP_TO_BORDER;
  case TextureWrapping::CLAMP_TO_EDGE:return GL_CLAMP_TO_EDGE;
  case TextureWrapping::REPEAT:return GL_REPEAT;
  case TextureWrapping::MIRRORED_REPEAT:return GL_MIRRORED_REPEAT;
  }

  return GL_REPEAT;
}
int getGLFilteringType(TextureFiltering filtering) {
  switch (filtering) {
  case TextureFiltering::NEAREST:return GL_NEAREST;
  case TextureFiltering::LINEAR:return GL_LINEAR;
  case TextureFiltering::TRILINEAR:
  case TextureFiltering::ANISOTROPIC:return GL_LINEAR;
  }

  return GL_NEAREST;
}

GLTexture::GLTexture(const std::shared_ptr<Image> &image, bool generateMipMaps,
                     TextureFiltering filtering,
                     TextureWrapping wrapping)
    : Texture(image, filtering, wrapping), texture() {
  glGenTextures(1, &this->texture);

  this->bind();

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, getGLWrappingType(wrapping));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, getGLWrappingType(wrapping));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, getGLFilteringType(filtering));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, getGLFilteringType(filtering));

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(),
               0, GL_RGB, GL_UNSIGNED_BYTE, image->getData());

  if (generateMipMaps) {
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  this->unbind();
}

void GLTexture::bind() {
  glBindTexture(GL_TEXTURE_2D, this->texture);
}

void GLTexture::unbind() {
  glBindTexture(GL_TEXTURE_2D, 0);
}
}