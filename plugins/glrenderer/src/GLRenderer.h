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

    public:
        std::string getName() override;

        std::shared_ptr<ui::Window> createRendererWindow(std::string name) override;

        std::shared_ptr<Shader> createShader(std::string source, Shader::Type type) override;

        std::shared_ptr<Mesh> createMesh(std::vector<float> vertices) override;

        std::shared_ptr<ShaderProgram> createShaderProgram() override;

        void render(const ObjectList &objectList) override;


    };

}


#endif //BLACKENGINE_GLRENDERER_H
