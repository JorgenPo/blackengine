//
// Created by popof on 09.10.2018.
//

#ifndef BLACKENGINE_GLRENDERER_H
#define BLACKENGINE_GLRENDERER_H

#include <CommonHeaders.h>
#include <render/RendererInterface.h>

#include "OpenGLCommonHeaders.h"

namespace black {

    /**
     * OpenGL v4.0 Renderer
     */
    class GLRenderer : public RendererInterface {
        std::shared_ptr<RenderTargetInterface> currentTarget;

    public:
        GLRenderer();

        void setCurrentRenderTarget(std::shared_ptr<RenderTargetInterface> target) override;

        void render(std::shared_ptr<Mesh> mesh) override;

        void setViewPort(int x, int y, int width, int height) override;
    };

}


#endif //BLACKENGINE_GLRENDERER_H
