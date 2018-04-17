//
// Created by popof on 16.04.2018.
//

#include "CorePlugin.h"

#include <iostream>
#include <memory>
#include <ui/glfwWindowFactory.h>
#include <core/Core.h>

using namespace std;

namespace black {

    std::string CorePlugin::getName() {
        return std::string("Core");
    }

    void CorePlugin::install() {
        auto core = Core::getInstance();
        auto glfwFactory = std::make_shared<ui::glfwWindowFactory>();

        core->registerWindowFactory(glfwFactory);
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