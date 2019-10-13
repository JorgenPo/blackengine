//
// Created by jorgen on 07.10.18.
//
#include "LinuxSharedLibrary.h"

#include <log/Logger.h>
#include <util/FileSystem.h>

namespace black::os {

LinuxSharedLibrary::LinuxSharedLibrary(const std::string &name)
    : AbstractSharedLibrary(name) {

}

void LinuxSharedLibrary::load() {
  auto name = this->name + ".so";

  if (!FileSystem::IsFileExist(name)) {
    throw LibraryNotFoundException(name);
  }

  this->handle = dlopen(name.c_str(), RTLD_LAZY);

  if (!this->handle) {
    throw LibraryLoadingException(name, dlerror());
  }
}

void LinuxSharedLibrary::unload() {
  if (this->handle) {
    dlclose(this->handle);
  }
}

void *LinuxSharedLibrary::getFunctionPointer(std::string name) {
  return dlsym(this->handle, name.c_str());
}
}