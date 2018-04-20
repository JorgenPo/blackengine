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
        virtual std::string getRenderTargetName() = 0;

        /**
         * Updates a renderer target. Apply all changes in context,
         * Swaps the buffers if double buffering enabled and so on.
         */
        virtual void updateRenderTarget() = 0;

        /**
         * Makes a renderer target current
         */
        virtual void setRenderTargetCurrent() = 0;
    };

}


#endif //BLACKENGINE_RENDERTARGET_H
