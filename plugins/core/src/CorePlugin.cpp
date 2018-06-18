//
// Created by popof on 16.04.2018.
//

#include "CorePlugin.h"
#include "FBXModelParser.h"
#include "SpectatorCamera.h"
#include "SimpleScene.h"
#include "FPSCamera.h"

#include <iostream>
#include <memory>
#include <core/Core.h>

using namespace std;

namespace black {

    std::string CorePlugin::getName() {
        return std::string("Core Plugin");
    }

    void CorePlugin::install() {
        auto core = Core::getInstance();
        core->registerScenePrototype(std::make_shared<scene::SimpleScene>(), "Simple Scene");
        core->registerModelParserPrototype("fbx", std::make_shared<parsers::FBXModelParser>());
        core->registerCameraPrototype("spectator", std::make_shared<SpectatorCamera>());
        core->registerCameraPrototype("fps", std::make_shared<FPSCamera>());
    }

    void CorePlugin::initialize() {
        cout << "initialize CorePlugin!" << endl;
    }

    void CorePlugin::shutdown() {
        cout << "shutdown CorePlugin!" << endl;
    }

    void CorePlugin::uninstall() {
        cout << "uninstall CorePlugin!" << endl;
    }
}