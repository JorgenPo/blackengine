//
// Created by popof on 29.09.2018.
//

#ifndef BLACKENGINE_OPENGLRENDERSYSTEM_H
#define BLACKENGINE_OPENGLRENDERSYSTEM_H

#include <CommonHeaders.h>
#include <render/RenderSystemInterface.h>

#include "OpenGLCommonHeaders.h"

#include "GLFWWindow.h"
#include "GLRenderer.h"
#include "GLTexture.h"

namespace black {
    /**
     * OpenGL v4.0 render system
     */
    class OpenGLRenderSystem : public RenderSystemInterface {
        std::shared_ptr<Logger> logger;
        std::shared_ptr<GLFWWindow> window;
        std::shared_ptr<GLRenderer> renderer;

    public:
        OpenGLRenderSystem();
        ~OpenGLRenderSystem();

        std::string getName() const override;

        void initialize(std::string title, int width, int height, bool isFullScreen) override;

        void shutdown() override;

        static std::string getErrorString(GLenum error);

        std::shared_ptr<RendererInterface> getRenderer() override;
        std::shared_ptr<AbstractRenderWindow> getRenderWindow() override;

        std::shared_ptr<Mesh> createMesh(std::vector<float> vertices, std::vector<float> textureCoords) override;

        std::shared_ptr<Shader> createShader(std::string source, Shader::Type type) override;
        std::shared_ptr<Texture> createTexture(const std::shared_ptr<Image> &image, bool generateMipMaps = true,
                                             TextureFiltering filtering = TextureFiltering::NEAREST,
                                             TextureWrapping wrapping = TextureWrapping::CLAMP_TO_BORDER) override;

        std::shared_ptr<ShaderProgram>
        createShaderProgram(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader) override;

        std::shared_ptr<SystemInterface> getSystemInterface() override;
    };
}


#endif //BLACKENGINE_OPENGLRENDERSYSTEM_H
