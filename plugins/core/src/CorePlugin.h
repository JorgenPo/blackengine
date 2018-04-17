//
// Created by popof on 16.04.2018.
//

#ifndef BLACKENGINE2018_COREPLUGIN_H
#define BLACKENGINE2018_COREPLUGIN_H

#include <core/Plugin.h>

namespace black {
    class CorePlugin : public Plugin {
    public:
        std::string getName() override;

        void install() override;

        void initialize() override;

        void shutdown() override;

        void uninstall() override;
    };
}


#endif //BLACKENGINE2018_COREPLUGIN_H
