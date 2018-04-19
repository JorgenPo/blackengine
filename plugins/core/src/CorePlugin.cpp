//
// Created by popof on 16.04.2018.
//

#include "CorePlugin.h"

#include <iostream>
#include <memory>
#include <core/Core.h>

using namespace std;

namespace black {

    std::string CorePlugin::getName() {
        return std::string("Core Plugin");
    }

    void CorePlugin::install() {
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