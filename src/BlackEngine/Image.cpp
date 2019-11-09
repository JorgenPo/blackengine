#include "Image.h"
#include "util/FileSystem.h"
#include "log/Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "exceptions/Exception.h"


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

void Image::load(const std::string& fileName, bool flipVertically) {
  stbi_set_flip_vertically_on_load(flipVertically);

  if (!FileSystem::IsFileExist(fileName)) {
    throw FileNotFoundException(fileName);
  }

  this->data = stbi_load(fileName.c_str(), &this->width, &this->height, &this->numColorChannels, 0);

  if (this->data == nullptr) {
    throw FailedToLoadImageException(fileName);
  }

  Logger::Get("Image")->debug("Loaded {} {}x{} image with {} color channels",
    fileName, width, height, numColorChannels);
}

bool Image::isLoaded() {
  return this->data != nullptr;
}

FailedToLoadImageException::FailedToLoadImageException(std::string_view fileName)
: Exception(fmt::format("File '{}' is corrupted or has unknown format", fileName)) {}
}