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
        std::shared_ptr<ShaderProgram> program;
        const std::string rendererName = "OpenGL Renderer";

        std::shared_ptr<Shader> createShader(const std::string &source, Shader::Type type) override;
        std::shared_ptr<Mesh> createMesh(std::vector<float> vertices, std::vector<unsigned int> indices) override;
        std::shared_ptr<ShaderProgram> createShaderProgram() override;

    public:
        std::string getName() override;

        std::shared_ptr<ui::Window> createRendererWindow(std::string name) override;

        void render(const GameEntityList &objectList) override;


        void initProgram();
    };

}


#endif //BLACKENGINE_GLRENDERER_H
