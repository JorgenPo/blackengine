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

        double time;

        std::shared_ptr<ShaderProgram> staticShader;
        std::shared_ptr<ShaderProgram> spriteShader;
        std::shared_ptr<ShaderProgram> terrainShader;

    public:
        void initialize() override;

        std::shared_ptr<Shader> createShader(const std::string &source, Shader::Type type) override;
        std::shared_ptr<Mesh> createMesh() override;
        std::shared_ptr<Texture> createTexture(std::shared_ptr<Image> image) override;
        std::shared_ptr<ShaderProgram> createShaderProgram();

        void setWireframeMode(bool on) override;

        void enableFaceCulling(Culling culling) override;

        void disableFaceCulling() override;

        void setFrontFace(FaceOrdering ordering) override;

        std::string getName() override;

        std::shared_ptr<ui::Window> createRendererWindow(std::string name) override;

        void render(const GameEntityList &objectList) override;

        std::shared_ptr<ShaderProgram> getStaticShader() override;

        std::shared_ptr<ShaderProgram> getTerrainShader() override;

        std::shared_ptr<ShaderProgram> getSpriteShader() override;

    private:
        void renderModel(const std::shared_ptr<GameEntity> &model, glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix);
    };

}


#endif //BLACKENGINE_GLRENDERER_H
