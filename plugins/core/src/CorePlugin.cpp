//
// Created by popof on 16.04.2018.
//

#include "CorePlugin.h"

#include <iostream>

using namespace std;

namespace black {

    std::string CorePlugin::getName() {
        return std::string("Core");
    }

    void CorePlugin::install() {
        cout << "install CorePlugin!" << endl;
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