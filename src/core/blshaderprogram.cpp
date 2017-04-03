#include "blshaderprogram.h"

#include <src/utils/bllogger.h>
#include <src/core/blconstants.h>

namespace black {

ShaderProgram::ShaderProgram()
    : QOpenGLShaderProgram(),
      m_vertex(), m_fragment()
{
}

ShaderProgram::ShaderProgram(std::shared_ptr<Shader> vertex,
                             std::shared_ptr<Shader> fragment)
    : ShaderProgram()
{
    create(vertex, fragment);
}

ShaderProgram::~ShaderProgram()
{
    m_fragment.reset();
    m_vertex.reset();
}

void ShaderProgram::create(std::shared_ptr<Shader> vertex,
                           std::shared_ptr<Shader> fragment)
{
    m_vertex.reset();
    m_vertex = vertex;
    m_fragment.reset();
    m_fragment = fragment;

    this->addShader(vertex->shader());
    this->addShader(fragment->shader());

    if ( !this->link() ) {
        Logger::getInstance() << this->log() << std::endl;

        // TODO: exceptions!
        throw "Failed to link shaders";
    }
}

bool ShaderProgram::link()
{
    this->bindLocations();

    return QOpenGLShaderProgram::link();
}

void ShaderProgram::setModelMatrix(const QMatrix4x4 &model)
{
    if ( !supportModelMatrix() ) {
        return;
    }

    this->setUniformValue("mModel", model);
}

void ShaderProgram::setCamera(const Camera* camera)
{
    if ( !supportCamera() ) {
        return;
    }

    setUniformValue("mView", camera->view());
    setUniformValue("mPerspective", camera->perspective());

    if ( !supportCameraPosition() ) {
        return;
    }

    this->setUniformValue("cameraPos", camera->position());
}

void ShaderProgram::setLight(const Light* light)
{
    if ( !supportLight() ) {
        return;
    }

    this->setUniformValue("lightPosition", light->position());
    this->setUniformValue("light.ambient", light->ambient());
    this->setUniformValue("light.diffuse", light->diffuse());
    this->setUniformValue("light.spectacular", light->spectacular());
}

void ShaderProgram::setMaterial(std::shared_ptr<Material> material)
{
    if ( !supportMaterials() ) {
        return;
    }

    this->setUniformValue("material.ambient", material->ambient());
    this->setUniformValue("material.diffuse", material->diffuse());
    this->setUniformValue("material.spectacular", material->spectacular());
    this->setUniformValue("material.shineFactor", material->shineFactor());
}

void ShaderProgram::enableTextures()
{
    if ( !this->supportTextures() ) {
        return;
    }

    this->setUniformValue("enableTextures", true);
}

void ShaderProgram::disableTextures()
{
    if ( !this->supportTextures() ) {
        return;
    }

    this->setUniformValue("enableTextures", false);
}

bool ShaderProgram::bind()
{
    bool res = QOpenGLShaderProgram::bind();
    defaultUniforms();

    return res;
}

std::string ShaderProgram::log() const
{
    return QOpenGLShaderProgram::log().toStdString();
}

/*
 * Strictly coded attribute locations. Why not?
*/
void ShaderProgram::bindLocations()
{
    this->bindAttributeLocation("vPosition", Constants::VERTEX_ATTR_POSITION);
    this->bindAttributeLocation("vNormal", Constants::VERTEX_ATTR_NORMAL);
    this->bindAttributeLocation("vTexCoords", Constants::VERTEX_ATTR_TEXCOORDS);
}

void ShaderProgram::defaultUniforms()
{
    this->enableTextures();
}

std::shared_ptr<Shader> ShaderProgram::fragment() const
{
    return m_fragment;
}

std::shared_ptr<Shader> ShaderProgram::vertex() const
{
    return m_vertex;
}

} // end of black namespace
