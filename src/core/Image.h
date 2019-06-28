//
// Created by popof on 25.04.2018.
//

#ifndef BLACKENGINE_IMAGE_H
#define BLACKENGINE_IMAGE_H

#include <CommonHeaders.h>

namespace black {
/**
 * Image file
 */
class BLACK_EXPORTED Image {
  int width;
  int height;
  int numColorChannels;
  unsigned char *data;

public:
  explicit Image(std::string fileName, bool flipVertically = false);

  virtual ~Image();

  /**
   * Loads an image from the file.
   *
   * @throws FileNotFoundException If file isn't exist
   * @param fileName
   */
  void load(std::string fileName, bool flipVertically = true);

  bool isLoaded();
  [[nodiscard]] int getWidth() const;
  [[nodiscard]] int getHeight() const;
  [[nodiscard]] int getNumColorChannels() const;
  [[nodiscard]] unsigned char *getData() const;
};
}

#endif //BLACKENGINE_IMAGE_H
