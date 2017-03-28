#include "diffuseshader.h"

DiffuseShader::DiffuseShader()
    : black::ShaderProgram()
{
    auto& rm = black::ResourceManager::getInstance();

    create(rm.get<black::Shader>("shaders/diffuse.vert"),
           rm.get<black::Shader>("shaders/diffuse.frag"));
}
