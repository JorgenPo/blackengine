#ifndef BLSHADER_H
#define BLSHADER_H

#include <src/core/blresourcemanager.h>
#include <src/core/blresource.h>

#include <QOpenGLShader>

#include <string>

namespace black {

class ResourceManager;
class ShaderProgram;

/**
 * @brief The Shader class
 * Just a slim wrapper around a QOpenGLShader class.
 * It's purpose generaly is to make possible to handle shaders
 * by Resource Manager class.
 *
 * @version 1.0 27.03.2017
 * First working version.
 *
 * @author george popof <popoff96@live.com>
 * @resource
 */
class Shader : public Resource
{
    friend class ResourceManager;
    friend class ShaderProgram;
public:
    Shader();
    Shader(std::string file);

    virtual ~Shader();

    bool isCompiled();
    std::string log() const;
    QOpenGLShader::ShaderType shaderType() const;

protected:
    QOpenGLShader* shader();

    // Resource interface
private:
    void load(std::string file) override;
public:
    std::string defaultName() override { return std::string("default.vert"); }
    std::string folderName()  override { return std::string("shaders");      }

private:
    QOpenGLShader* m_shader;
};

} // end of black namespace
#endif // BLSHADER_H
