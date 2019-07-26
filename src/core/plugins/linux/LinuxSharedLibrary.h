//
// Created by jorgen on 07.10.18.
//

#ifndef BLACKENGINE_LINUXSHAREDLIBRARY_H
#define BLACKENGINE_LINUXSHAREDLIBRARY_H

#include <common/PlatformHeaders.h>
#include <plugins/AbstractSharedLibrary.h>

namespace black::os {
/**
 * Linux so dynamic library class
 */
class LinuxSharedLibrary : public AbstractSharedLibrary {
private:
  void *handle;

public:
  explicit LinuxSharedLibrary(const std::string &name);

  void load() override;
  void unload() override;

private:
  void *getFunctionPointer(std::string name) override;
};
}

#endif //BLACKENGINE_LINUXSHAREDLIBRARY_H
