//
// Created by popof on 01.11.2018.
//

#include <BlackEngine/util/ModelManager.h>

#include "ModelParsersPlugin.h"
#include "parsers/ObjParser.h"

namespace black {

std::string ModelParsersPlugin::getName() {
  return "ModelParsers";
}

void ModelParsersPlugin::install() {
  ModelManager::AddModelParser("obj", std::make_shared<ObjParser>());
}

void ModelParsersPlugin::initialize() {

}

void ModelParsersPlugin::shutdown() {

}

void ModelParsersPlugin::uninstall() {

}
}