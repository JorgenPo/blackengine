#include "Texture.h"
#include <Engine.h>

namespace black {
    Texture::Texture(std::shared_ptr<Image> image, bool generateMipMaps, TextureFiltering filtering, TextureWrapping wrapping)
        : filtering(filtering), wrapping(wrapping) {
    }

    TextureFiltering Texture::getFiltering() const {
        return filtering;
    }

    TextureWrapping Texture::getWrapping() const {
        return wrapping;
    }

    Texture::~Texture() = default;
}
