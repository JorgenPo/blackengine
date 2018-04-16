//
// Created by popof on 15.04.2018.
//

#ifndef BLACKENGINE2018_WINDOWFACTORY_H
#define BLACKENGINE2018_WINDOWFACTORY_H

#include <memory>
#include "Window.h"

namespace black::ui {
    /**
     * A Window factory class responsible for
     * creating abstract window classes.
     */
    class WindowFactory {
    protected:
        std::string title;
        int width;
        int height;

    public:
        virtual std::shared_ptr<Window> create() = 0;

        void setTitle(const std::string &title) {
            WindowFactory::title = title;
        }

        void setWidth(int width) {
            WindowFactory::width = width;
        }

        void setHeight(int height) {
            WindowFactory::height = height;
        }
    };
}

#endif //BLACKENGINE2018_WINDOWFACTORY_H
