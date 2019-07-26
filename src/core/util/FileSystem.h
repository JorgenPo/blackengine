//
// Created by popof on 31.10.2018.
//

#ifndef BLACKENGINE_PATHS_H
#define BLACKENGINE_PATHS_H

#include <common/Exported.h>
#include <string>

namespace black {

/**
 * Helper methods for working with paths and file names
 */
class BLACK_EXPORTED FileSystem {
public:
  /**
   * Return a file extension without a dot.
   *
   * @param path Path to the file
   *
   * @return File extension
   */
  static std::string GetFileExtension(std::string path);

  /**
   * Check file existing
   *
   * @param path Path to the file
   *
   * @return Is the file exist
   */
  static bool IsFileExist(std::string path);

  /**
   * Write string data to a file. If create flag is true
   * then file will be created if not exist
   *
   * @param fileName
   * @param content
   * @param create
   *
   * @return
   */
  static void SaveToFile(std::string_view fileName, const std::string &content, bool create);
};

}

#endif //BLACKENGINE_PATHS_H
