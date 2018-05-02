//
// Created by popof on 20.04.2018.
//

#ifndef BLACKENGINE_GLRENDERER_H
#define BLACKENGINE_GLRENDERER_H

#include <core/render/Renderer.h>

namespace black::render {

    /**
     * OpenGL Renderer
     */
    class GLRenderer : public Renderer {
        const std::string rendererName = "OpenGL Renderer";

        std::shared_ptr<Shader> createShader(const std::string &source, Shader::Type type) override;
        std::shared_ptr<Mesh> createMesh() override;
        std::shared_ptr<ShaderProgram> createShaderProgram() override;
        std::shared_ptr<Texture> createTexture(std::shared_ptr<Image> image) override;

    public:
        void setWireframeMode(bool on) override;

        void enableFaceCulling(Culling culling) override;

        void disableFaceCulling() override;

        void setFrontFace(FaceOrdering ordering) override;

        std::string getName() override;

        std::shared_ptr<ui::Window> createRendererWindow(std::string name) override;

        void render(const GameEntityList &objectList) override;
    };

}


#endif //BLACKENGINE_GLRENDERER_H
