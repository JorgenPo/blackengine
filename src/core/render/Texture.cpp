//
// Created by popof on 25.04.2018.
//

#include "Texture.h"
#include <utility>
#include <core/Exception.h>
#include <core/Core.h>

namespace black::render {
    Texture::Texture(std::shared_ptr<Image> image, bool generateMipMaps, TextureFiltering filtering, TextureWrapping wrapping)
            : filtering(filtering), wrapping(wrapping) {

    }

    std::shared_ptr<Texture> Texture::fromFile(std::string fileName) {
        auto image = std::make_shared<Image>(std::move(fileName));

        if (!image->isLoaded()) {
            throw FileNotFoundException(fileName);
        }

        auto texture = Core::getInstance()->getCurrentRenderer()->createTexture(image);

        return texture;
    }

    TextureFiltering Texture::getFiltering() const {
        return filtering;
    }

    TextureWrapping Texture::getWrapping() const {
        return wrapping;
    }

    Texture::~Texture() = default;
}
