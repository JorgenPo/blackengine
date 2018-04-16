//
// Created by popof on 15.04.2018.
//

#include "Core.h"

namespace black {
    Core::Core() {
        // 10 is enough almost for now
        this->factories.reserve(10);
    }

    void Core::addWindowFactory(std::shared_ptr<ui::WindowFactory> factory) {
        this->factories.push_back(factory);
    }

    std::vector<std::shared_ptr<ui::WindowFactory>> Core::getWindowFactories() {
        return std::vector<std::shared_ptr<ui::WindowFactory>>();
    }
}
