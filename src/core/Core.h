//
// Created by popof on 15.04.2018.
//

#ifndef BLACKENGINE2018_CORE_H
#define BLACKENGINE2018_CORE_H

#include <memory>
#include <vector>

#include <core/ui/WindowFactory.h>

namespace black::core {
    /**
     * Responsible for register components and provide
     *  components runtime
     *
     *  @singleton
     */
    class Core {
        std::vector<std::shared_ptr<ui::WindowFactory>> factories;

    private:
        Core();

    public:
        static Core& getInstance() {
            static Core instance;
            return instance;
        }

        void addWindowFactory(std::shared_ptr<ui::WindowFactory> factory);
        std::vector<std::shared_ptr<ui::WindowFactory>> getWindowFactories();
    };

}
#endif //BLACKENGINE2018_CORE_H
