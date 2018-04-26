//
// Created by popof on 16.04.2018.
//

#include "CorePlugin.h"
#include "SimpleScene.h"
#include "BlackModelParser.h"

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
        core->registerScenePrototype(std::make_shared<scene::SimpleScene>());
        core->registerModelParserPrototype("bmf", std::make_shared<parsers::BlackModelParser>());
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