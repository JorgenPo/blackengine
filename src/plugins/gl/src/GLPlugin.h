//
// Created by popof on 27.09.2018.
//

#ifndef BLACKENGINE_GLPLUGIN_H
#define BLACKENGINE_GLPLUGIN_H

#include <plugins/PluginInterface.h>

namespace black {

class GLPlugin : public PluginInterface {
  static std::shared_ptr<Logger> logger;

public:
  GLPlugin();

  std::string getName() override;

  void install() override;

  void initialize() override;

  void shutdown() override;

  void uninstall() override;
};

}

#endif //BLACKENGINE_GLPLUGIN_H
