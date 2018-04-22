//
// Created by popof on 19.04.2018.
//

#ifndef BLACKENGINE_RENDER_H
#define BLACKENGINE_RENDER_H

#include <memory>
#include <list>
#include <core/ui/Window.h>
#include <core/Color.h>

#include "RenderTarget.h"
#include "Object.h"
#include "Shader.h"
#include "Mesh.h"
#include "ShaderProgram.h"

namespace black::render {
    using RenderTargetList = std::list<std::shared_ptr<RenderTarget>>;

    /**
     * Abstract class for all renderers.
     */
    class Renderer {
    protected:
        RenderTargetList renderTargets;
        Color clearColor;

    public:
        Renderer();

        virtual std::string getName() = 0;
        virtual std::shared_ptr<ui::Window> createRendererWindow(std::string name) = 0;
        virtual std::shared_ptr<Shader> createShader(std::string source, Shader::Type type) = 0;
        virtual std::shared_ptr<ShaderProgram> createShaderProgram() = 0;
        virtual std::shared_ptr<Mesh> createMesh(std::vector<float> vertices) = 0;

        /**
         * Renders all object to current render target.
         * Target is current prior call of this method, after
         * this method render target will be updated.
         *
         * @param objectList Objects to render
         */
        virtual void render(const ObjectList &objectList);

        void addRenderTarget(std::shared_ptr<RenderTarget> target);
        void removeRenderTarget(std::string name);
        RenderTargetList &getRenderTargets();

        void renderToAllTargets(const ObjectList &objectList);
        void renderToTarget(std::string targetName, const ObjectList &objectList);

        const Color &getClearColor() const;

        void setClearColor(const Color &clearColor);
    };
}


#endif //BLACKENGINE_RENDER_H
