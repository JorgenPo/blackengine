//
// Created by popov on 07.07.2019.
//

#include "ApplicationShader.h"
#include "ShaderProgram.h"

namespace black {

ApplicationShader::~ApplicationShader() = default;

ApplicationShader::ApplicationShader(std::shared_ptr<ShaderProgram> impl) : impl(std::move(impl)) {

}

void ApplicationShader::use() {
  impl->use();
}

}
