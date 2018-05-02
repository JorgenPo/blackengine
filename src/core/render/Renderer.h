//
// Created by popof on 19.04.2018.
//

#ifndef BLACKENGINE_RENDER_H
#define BLACKENGINE_RENDER_H

#include <memory>
#include <list>
#include <core/ui/Window.h>
#include <core/Color.h>
#include <core/Camera.h>

#include "RenderTarget.h"
#include "core/GameEntity.h"
#include "Shader.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"

namespace black::render {
    using RenderTargetList = std::list<std::shared_ptr<RenderTarget>>;

    enum class Culling {
        FRONT,
        BACK,
        BOTH
    };

    /**
     * Abstract class for all renderers.
     */
    class Renderer {
    protected:
        std::shared_ptr<RenderTarget> currentRenderTarget;
        float deltaTime;

        std::shared_ptr<Camera> rendererView;
    protected:
        RenderTargetList renderTargets;
        Color clearColor;

    public:
        Renderer();

        virtual std::string getName() = 0;

        virtual std::shared_ptr<ui::Window> createRendererWindow(std::string name) = 0;
        virtual std::shared_ptr<Shader> createShader(const std::string &source, Shader::Type type) = 0;
        virtual std::shared_ptr<ShaderProgram> createShaderProgram() = 0;
        virtual std::shared_ptr<Mesh> createMesh() = 0;
        virtual std::shared_ptr<Texture> createTexture(std::shared_ptr<Image> image) = 0;

        virtual void setWireframeMode(bool on) = 0;
        virtual void setFaceCulling(Culling culling) = 0;

        /**
         * Renders all object to current render target.
         * Target is current prior call of this method, after
         * this method render target will be updated.
         *
         * @param objectList Objects to render
         */
        virtual void render(const GameEntityList &objectList);

        void addRenderTarget(std::shared_ptr<RenderTarget> target);
        void removeRenderTarget(std::string name);
        RenderTargetList &getRenderTargets();

        void renderToAllTargets(const GameEntityList &objectList);
        void renderToTarget(std::string targetName, const GameEntityList &objectList);

        const Color &getClearColor() const;

        void setClearColor(const Color &clearColor);

        /**
         * Returns a time last frame render took
         * @return
         */
        float getDeltaTime() const;

        const std::shared_ptr<Camera> &getRendererView() const;

        void setRendererView(const std::shared_ptr<Camera> &rendererView);

        void updateRendererView() const;
    };
}


#endif //BLACKENGINE_RENDER_H
