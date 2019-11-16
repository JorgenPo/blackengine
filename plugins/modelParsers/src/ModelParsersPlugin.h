//
// Created by popof on 01.11.2018.
//

#ifndef BLACKENGINE_MODELPARSERSPLUGIN_H
#define BLACKENGINE_MODELPARSERSPLUGIN_H

#include <BlackEngine/common/CommonHeaders.h>
#include <plugins/PluginInterface.h>

namespace black {
/**
 * Model parsers plugin provides some model parsers to the engine
 */
class ModelParsersPlugin : public PluginInterface {
public:
  std::string getName() override;

  void install() override;

  void initialize() override;

  void shutdown() override;

  void uninstall() override;
};
}

#endif //BLACKENGINE_MODELPARSERSPLUGIN_H
