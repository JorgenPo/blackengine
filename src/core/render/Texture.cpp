//
// Created by popof on 25.04.2018.
//

#include "Texture.h"
#include <utility>

namespace black::render {
    Texture::Texture(std::shared_ptr<Image> image, bool generateMipMaps, TextureFiltering filtering, TextureWrapping wrapping)
            : image(std::move(image)), filtering(filtering), wrapping(wrapping) {

    }

    const std::shared_ptr<Image> &Texture::getImage() const {
        return image;
    }

    std::shared_ptr<Texture> Texture::fromFile(std::string fileName) {
        return std::shared_ptr<Texture>();
    }

    TextureFiltering Texture::getFiltering() const {
        return filtering;
    }

    TextureWrapping Texture::getWrapping() const {
        return wrapping;
    }
}
