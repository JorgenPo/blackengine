#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <exceptions/Exception.h>

namespace black {

Image::Image(std::string fileName, bool flipVertically)
  : width(), height(), numColorChannels(), data(nullptr) {
  this->load(std::move(fileName), flipVertically);
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

void Image::load(std::string fileName, bool flipVertically) {
  stbi_set_flip_vertically_on_load(flipVertically);

  this->data = stbi_load(fileName.c_str(), &this->width, &this->height, &this->numColorChannels, 0);

  if (this->data == nullptr) {
    throw FileNotFoundException(fileName);
  }
}

bool Image::isLoaded() {
  return this->data != nullptr;
}
}