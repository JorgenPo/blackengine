//
// Created by popov on 29.06.2019.
//

#include "ShaderManager.h"

#include <Engine.h>
#include <shader/ShaderProgram.h>
#include <render/RenderSystemInterface.h>

#include <fstream>

namespace black::util {

std::shared_ptr<Shader> black::util::ShaderManager::CreateShaderFromFile(
    std::string_view fileName, black::Shader::Type type) {
  std::ifstream file(fileName.data());

  if (!file.is_open()) {
    throw FileNotFoundException(fileName.data());
  }

  std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  auto rs = Engine::GetCurrentRenderSystem();

  auto shader = rs->createShader(std::move(content), type);
  shader->compile();

  return shader;
}

std::shared_ptr<ShaderProgram> ShaderManager::CreateShaderProgramFromFile(
    std::string_view vertexShaderFile, std::string_view fragmentShaderFile) {
  auto vertexShader = CreateShaderFromFile(vertexShaderFile, Shader::Type::VERTEX);
  auto fragmentShader = CreateShaderFromFile(fragmentShaderFile, Shader::Type::FRAGMENT);

  auto rs = Engine::GetCurrentRenderSystem();
  auto program = rs->createShaderProgram(std::move(vertexShader), std::move(fragmentShader));

  program->link();

  return program;
}


}
