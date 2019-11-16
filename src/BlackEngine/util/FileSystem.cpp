//
// Created by popof on 31.10.2018.
//

#include "FileSystem.h"
#include "Strings.h"

#include "../exceptions/Exception.h"
#include <BlackEngine/log/Logger.h>

#include <memory>

#include <boost/filesystem.hpp>

namespace black {

std::string FileSystem::GetFileExtension(std::string path) {
  auto splitVector = Strings::Split(std::move(path), ".");

  if (splitVector.size() < 2) {
    return "";
  }

  // Return the last element as an extension
  return splitVector.back();
}

bool FileSystem::IsFileExist(std::string_view path) {
  return boost::filesystem::exists(path.data());
}

void FileSystem::SaveToFile(std::string_view fileName, const std::string &content, bool create) {
  auto log = Logger::Get("FileSystem");

  auto isFileExists = IsFileExist(fileName.data());
  if (!isFileExists && !create) {
    throw FileNotFoundException(fileName.data());
  }

  if (!isFileExists) {
    log->debug("Creating new file '{0}'", fileName);
  }
  std::ofstream file(fileName.data());
  file << content;

  file.flush();
}
}