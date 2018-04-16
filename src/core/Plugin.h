//
// Created by popof on 16.04.2018.
//

#ifndef BLACKENGINE2018_PLUGIN_H
#define BLACKENGINE2018_PLUGIN_H

#include <string>

namespace black {

    /**
     * Extention plugin class
     */
    class Plugin {
        virtual std::string getName() = 0;

        // Plugin lifecycle. Inpired by Ogre:3
        virtual void install() = 0;
        virtual void initialize() = 0;
        virtual void shutdown() = 0;
        virtual void uninstall() = 0;
    };

}


#endif //BLACKENGINE2018_PLUGIN_H
