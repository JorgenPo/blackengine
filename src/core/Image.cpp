//
// Created by popof on 25.04.2018.
//

#include "Image.h"
#include "Exception.h"
#include "Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace black {

    std::shared_ptr<Image> Image::fromFile(std::string fileName) {
        return std::shared_ptr<Image>();
    }

    Image::Image(std::string fileName) {
        try {
            this->load(std::move(fileName));
        } catch(const FileNotFoundException &e) {
            // Do nothing
        }
    }

    Image::~Image() {
        stbi_image_free(this->data);
    }

    int Image::getWidth() const {
        return width;
    }

    int Image::getHeight() const {
        return height;
    }

    int Image::getNumColorChannels() const {
        return numColorChannels;
    }

    unsigned char *Image::getData() const {
        return data;
    }

    void Image::load(std::string fileName) {
        this->data = stbi_load(fileName.c_str(), &this->width, &this->height, &this->numColorChannels, 0);

        if (this->data == nullptr) {
            throw FileNotFoundException(fileName);
        }
    }

    bool Image::isLoaded() {
        return this->data != nullptr;
    }
}