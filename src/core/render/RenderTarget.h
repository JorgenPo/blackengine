//
// Created by popof on 19.04.2018.
//

#ifndef BLACKENGINE_RENDERTARGET_H
#define BLACKENGINE_RENDERTARGET_H

#include <string>

namespace black::render {

    /**
     * Represents an object on which render can render
     * scene
     */
    class RenderTarget {

    public:
        virtual std::string getName() = 0;

    };

}


#endif //BLACKENGINE_RENDERTARGET_H
