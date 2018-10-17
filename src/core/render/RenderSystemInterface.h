//
// Created by popof on 29.09.2018.
//

#ifndef BLACKENGINE_RENDERSYSTEMINTERFACE_H
#define BLACKENGINE_RENDERSYSTEMINTERFACE_H

#include <CommonHeaders.h>
#include <Mesh.h>
#include "RendererInterface.h"
#include "AbstractRenderWindow.h"

namespace black {

    class RenderSystemInitializationException : public Exception {
    public:
        explicit RenderSystemInitializationException(const std::string &message) : Exception(message) {
        }
    };

    class RenderSystemInterface {
    public:
        /**
         * Return an unique render system name.
         *
         * @return Name of the render system.
         */
        virtual std::string getName() const = 0;

        /**
         * Initialize a render system.
         * Also will initialize the renderer and main render window.
         *
         * @throws RenderSystemInitializationException
         */
        virtual void initialize(std::string title, int width, int height, bool isFullScreen) = 0;

        /**
         * Shutdown a render system.
         */
        virtual void shutdown() = 0;

        /**
         * Create an appropriate render system render and render window.
         *
         * @return Renderer for this render system
         */
        virtual std::shared_ptr<RendererInterface> getRenderer() = 0;

        /**
         * Return a main renderer window
         *
         * @return Pointer for the renderer window
         */
        virtual std::shared_ptr<AbstractRenderWindow> getRenderWindow() = 0;

        /**
         * Create a mesh
         *
         * @return Pointer to the created mesh
         */
        virtual std::shared_ptr<Mesh> createMesh(std::vector<float> vertices) = 0;
    };
}


#endif //BLACKENGINE_RENDERSYSTEMINTERFACE_H
