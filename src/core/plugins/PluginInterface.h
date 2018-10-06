//
// Created by popof on 26.09.2018.
//

#ifndef BLACKENGINE_PLUGININTERFACE_H
#define BLACKENGINE_PLUGININTERFACE_H

#include "CommonHeaders.h"

namespace black {

    /**
     * Interface for all plugins. Plugin is a dynamic linked library contain
     * some extension to the Engine core.
     */
    class BLACK_EXPORTED PluginInterface {

    public:
        virtual std::string getName() = 0;

        // Plugin lifecycle. Inspired by Ogre Engine

        /**
         *  Install plugin, register needed objects.
         *  You can not use other plugins on this step.
         */
        virtual void install() = 0;

        /**
         * On this step you can use other plugins and Engine objects if you like.
         */
        virtual void initialize() = 0;

        /**
         *  Shutdown a plugin, free all resources.
         */
        virtual void shutdown() = 0;

        /**
         * Finally remove all plugin resources, on this step you can not be sure that any
         * other plugin is still alive.
         */
        virtual void uninstall() = 0;
    };
}

#endif //BLACKENGINE_PLUGININTERFACE_H
