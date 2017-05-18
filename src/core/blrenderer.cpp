#include "blrenderer.h"

#include <blobjectcamera.h>

namespace black {

Renderer::Renderer()
    : m_program(), m_camera()
{
    initializeOpenGLFunctions();

    // Default program. Can be changed any time
    auto& rm = ResourceManager::getInstance();

    m_program = new ShaderProgram(
                rm.get<Shader>(std::string(Constants::DEFAULT_PROGRAM) + ".vert"),
                rm.get<Shader>(std::string(Constants::DEFAULT_PROGRAM) + ".frag"));

    m_camera = std::make_shared<ObjectCamera>();
    m_light = std::make_shared<Light>();
}

Renderer::~Renderer()
{
    m_camera.reset();
    m_light.reset();
}

std::shared_ptr<Light> Renderer::getLight() const
{
    return m_light;
}

void Renderer::setLight(const std::shared_ptr<Light> &light)
{
    m_light = light;
    m_program->setLight(light);
}

std::shared_ptr<Camera> Renderer::getCamera() const
{
    return m_camera;
}

void Renderer::setCamera(const std::shared_ptr<Camera> &camera)
{
    m_camera = camera;
    m_program->setCamera(camera);
}

const ShaderProgram* Renderer::getProgram() const
{
    return m_program;
}

void Renderer::renderModel(const std::shared_ptr<Model> &model)
{
    m_program->setModelMatrix(model->modelMatrix());
    m_program->setMaterial(model->material());

    if ( !model->isInitialized() ) {
        Logger::getInstance("error") << "Trying to render empty model "
                                     << "(no mesh provided)" << std::endl;
        return;
    }

    model->bind();

    if ( model->isIndexed() ) {
        glDrawElements(GL_TRIANGLES, model->vertexCount(), GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, model->vertexCount());
    }

    model->release();
}

void Renderer::renderTerrain(const std::shared_ptr<Terrain> &terrain)
{
    m_program->setModelMatrix(terrain->modelMatrix());
    m_program->setMaterial(terrain->material());

    terrain->bind();

    glDrawArrays(GL_TRIANGLES, 0, terrain->vertexCount());

    terrain->release();
}

void Renderer::setProgram(const std::unique_ptr<ShaderProgram>& program)
{
    m_program->release();
    m_program = std::move(program).get();
    m_program->bind();
}

} // end of black namespace
