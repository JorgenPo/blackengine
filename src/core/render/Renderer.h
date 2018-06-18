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

    enum class FaceOrdering {
        CW,     // Clockwise
        CCW,    // Counter Clockwise
    };

    /**
     * Abstract class for all renderers.
     */
    class Renderer {
    protected:
        std::shared_ptr<RenderTarget> currentRenderTarget;
        std::shared_ptr<Camera> rendererView;

        RenderTargetList renderTargets;
        Color clearColor;

    public:
        Renderer();

        virtual std::string getName() = 0;

        virtual void initialize() = 0;

        virtual std::shared_ptr<ui::Window> createRendererWindow(std::string name) = 0;
        virtual std::shared_ptr<Shader> createShader(const std::string &source, Shader::Type type) = 0;
        virtual std::shared_ptr<Mesh> createMesh() = 0;
        virtual std::shared_ptr<Texture> createTexture(std::shared_ptr<Image> image) = 0;
        virtual std::shared_ptr<ShaderProgram> createShaderProgram() = 0;

        virtual void setWireframeMode(bool on) = 0;
        virtual void enableFaceCulling(Culling culling) = 0;
        virtual void disableFaceCulling() = 0;
        virtual void setFrontFace(FaceOrdering ordering) = 0;

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

        const std::shared_ptr<Camera> &getRendererView() const;

        void setRendererView(const std::shared_ptr<Camera> &rendererView);

        void updateRendererView() const;

        virtual std::shared_ptr<ShaderProgram> getStaticShader() = 0;
        virtual std::shared_ptr<ShaderProgram> getTerrainShader() = 0;
        virtual std::shared_ptr<ShaderProgram> getSpriteShader() = 0;
    };
}


#endif //BLACKENGINE_RENDER_H
