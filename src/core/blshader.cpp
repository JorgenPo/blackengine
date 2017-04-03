#include "blshader.h"

#include <src/utils/bllogger.h>

namespace black {

Shader::Shader()
    : m_shader()
{

}

Shader::Shader(std::string file)
    : m_shader()
{
    this->load(file);
}

Shader::~Shader()
{
    delete m_shader;
}

bool Shader::isCompiled()
{
    return m_shader->isCompiled();
}

std::string Shader::log() const
{
    return m_shader->log().toStdString();
}

QOpenGLShader::ShaderType Shader::shaderType() const
{
    return m_shader->shaderType();
}

QOpenGLShader *Shader::shader()
{
    return m_shader;
}

void Shader::load(std::string file)
{
    Logger::getInstance() << "Loading " << file << " shader...";

    size_t dotPos = file.find_last_of(".");

    std::string sub = file.substr(dotPos + 1);
    if ( sub == "frag" ) {
        m_shader = new QOpenGLShader(QOpenGLShader::Fragment);
    } else {
        m_shader = new QOpenGLShader(QOpenGLShader::Vertex);
    }

    m_shader->compileSourceFile(file.c_str());

    if ( !m_shader->isCompiled() ) {
        Logger::getInstance("error") << this->log() << std::endl;
        throw "Failed to compile shaders"; // TODO: exceptions
    }

    Logger::getInstance() << " Done! " << std::endl;
}

} // end of black namespace
