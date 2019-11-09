#include "Texture.h"
#include "../Engine.h"

namespace black {
Texture::Texture(const std::shared_ptr<Image>& image,
                 TextureFiltering filtering,
                 TextureWrapping wrapping)
    : image(image), filtering(filtering), wrapping(wrapping) {
}

TextureFiltering Texture::getFiltering() const {
  return filtering;
}

TextureWrapping Texture::getWrapping() const {
  return wrapping;
}

Texture::~Texture() = default;
}
