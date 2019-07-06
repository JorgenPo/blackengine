//
// Created by popof on 25.10.2018.
//

#include "ModelManager.h"
#include "FileSystem.h"
#include "ModelParser.h"

#include <Engine.h>

#include <log/Logger.h>
#include <render/Material.h>
#include <render/RenderSystemInterface.h>

#include <components/ModelComponent.h>

#include <memory>
#include <fstream>
#include <utility>

namespace black {

std::unordered_map<std::string, std::shared_ptr<ModelParser>> ModelManager::parsers;

std::shared_ptr<ModelComponent> ModelManager::CreateSquare(float sideSize) {
  const auto halfSide = sideSize / 2;

  auto mesh = Engine::GetCurrentRenderSystem()->createMesh({
       halfSide, halfSide, 0.0f,
       -halfSide, halfSide, 0.0f,
       halfSide, -halfSide, 0.0f,
       -halfSide, halfSide, 0.0f,
       -halfSide, -halfSide, 0.0f,
       halfSide, -halfSide, 0.0f,}, {
       halfSide, halfSide, 0.0f,
       -halfSide, halfSide, 0.0f,
       halfSide, -halfSide, 0.0f,
       -halfSide, halfSide, 0.0f,
       -halfSide, -halfSide, 0.0f,
       halfSide, -halfSide, 0.0f,}, {});

  return ModelManager::CreateFromMesh(mesh);
}

std::shared_ptr<ModelComponent> ModelManager::CreateFromMesh(std::shared_ptr<Mesh> mesh) {
  auto modelPart = ModelPart("Default", std::move(mesh), Material{});

  std::vector<ModelPart> parts;
  parts.emplace_back(modelPart);

  return std::make_shared<ModelComponent>(parts);
}

std::shared_ptr<ModelComponent> ModelManager::CreateEquilateralTriangle(float sideSize) {
  const auto halfSide = sideSize / 2;

  auto mesh = Engine::GetCurrentRenderSystem()->createMesh({
                                                               0.0f, halfSide, 0.0f,
                                                               -halfSide, -halfSide, 0.0f,
                                                               halfSide, -halfSide, 0.0f,}, {
                                                               0.0f, halfSide, 0.0f,
                                                               -halfSide, -halfSide, 0.0f,
                                                               halfSide, -halfSide, 0.0f,}, {});

  return ModelManager::CreateFromMesh(mesh);
}

std::shared_ptr<ModelComponent> ModelManager::CreateRectangle(float a, float b) {
  const auto halfA = a / 2;
  const auto halfB = b / 2;

  auto mesh = Engine::GetCurrentRenderSystem()->createMesh({
                                                               halfA, halfB, 0.0f,
                                                               -halfA, halfB, 0.0f,
                                                               halfA, -halfB, 0.0f,
                                                               -halfA, halfB, 0.0f,
                                                               -halfA, -halfB, 0.0f,
                                                               halfA, -halfB, 0.0f,
                                                           }, {
                                                               halfA, halfB, 0.0f,
                                                               -halfA, halfB, 0.0f,
                                                               halfA, -halfB, 0.0f,
                                                               -halfA, halfB, 0.0f,
                                                               -halfA, -halfB, 0.0f,
                                                               halfA, -halfB, 0.0f,
                                                           }, {});

  return ModelManager::CreateFromMesh(mesh);
}

std::shared_ptr<ModelComponent> ModelManager::CreateFromFile(const std::string& fileName) {
  auto extension = FileSystem::GetFileExtension(fileName);
  auto logger = Logger::Get("ModelManager");

  std::shared_ptr<ModelComponent> model;
  try {
    auto parser = parsers.at(extension);

    if (!FileSystem::IsFileExist(fileName)) {
      throw FileNotFoundException(fileName);
    }

    parser->parse(fileName);
    model = parser->getModel();
  } catch (const std::out_of_range &e) {
    logger->debug("No model parser for '{0}' extension", extension);
    throw UnknownFormatException(extension);
  } catch (const ParseException &e) {
    logger->error("Failed to parse model from file '{0}': {1}", fileName, e.getMessage());
    throw;
  } catch (const FileNotFoundException &e) {
    logger->debug("File '{0}' does not exists", fileName);
    throw;
  }

  return model;
}

void ModelManager::AddModelParser(const std::string& extension, std::shared_ptr<ModelParser> parser) {
  parsers[extension] = std::move(parser);
}

UnknownFormatException::UnknownFormatException(const std::string& extension) {
  this->message << "No parser for '" << extension << "' model found!" << std::endl;
}
}