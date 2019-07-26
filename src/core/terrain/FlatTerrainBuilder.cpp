//
// Created by popov on 25.07.2019.
//

#include "FlatTerrainBuilder.h"

#include <Engine.h>
#include <log/Logger.h>
#include <render/RenderSystemInterface.h>
#include <components/ModelComponent.h>
#include <util/ModelManager.h>
#include <components/TerrainComponent.h>

namespace black {

float getHeightAt(size_t x, size_t y) {
  return 0.0f;
}

std::shared_ptr<ModelComponent> makeModel(const TerrainBuilder::Data &data) {
  std::vector<float> vertices;
  std::vector<float> uvs;
  std::vector<float> normals;

  auto width = data.width;
  auto height = data.height;
  auto levelOfDetails = data.lod.getValue();

  auto tileWidth = width / static_cast<float>(levelOfDetails);
  auto tileHeight = height / static_cast<float>(levelOfDetails);
  auto rows = width / tileWidth;

  vertices.reserve(rows * rows * 4);

  float xCoord;
  float zCoord;
  float halfWidth = width / 2;
  float halfHeight = height / 2;
  unsigned int currentIndex = 0;

  for (size_t xIndex = 0; xIndex < rows; xIndex++) {
    for (size_t zIndex = 0; zIndex < rows; zIndex++) {
      xCoord = xIndex * tileWidth;
      zCoord = zIndex * tileHeight;

      // Add cell vertices
      // Bottom left
      // Terrain must be rendered in center, so adjust x and y

      // Top left
      vertices.push_back(xCoord - halfWidth);
      vertices.push_back(getHeightAt(xIndex, zIndex));
      vertices.push_back(zCoord + tileHeight - halfHeight);

      // Top right
      vertices.push_back(xCoord + tileWidth - halfWidth);
      vertices.push_back(getHeightAt(xIndex, zIndex));
      vertices.push_back(zCoord + tileHeight - halfHeight);

      // Bottom right
      vertices.push_back(xCoord + tileWidth - halfWidth);
      vertices.push_back(getHeightAt(xIndex, zIndex));
      vertices.push_back(zCoord - halfHeight);

      // Botton left
      vertices.push_back(xCoord - halfWidth);
      vertices.push_back(getHeightAt(xIndex, zIndex));
      vertices.push_back(zCoord - halfHeight);

      // Top left
      vertices.push_back(xCoord - halfWidth);
      vertices.push_back(getHeightAt(xIndex, zIndex));
      vertices.push_back(zCoord + tileHeight - halfHeight);

      // Bottom right
      vertices.push_back(xCoord + tileWidth - halfWidth);
      vertices.push_back(getHeightAt(xIndex, zIndex));
      vertices.push_back(zCoord - halfHeight);

      // Normals
      normals.push_back(0.0f);
      normals.push_back(1.0f);
      normals.push_back(0.0f);

      normals.push_back(0.0f);
      normals.push_back(1.0f);
      normals.push_back(0.0f);

      normals.push_back(0.0f);
      normals.push_back(1.0f);
      normals.push_back(0.0f);

      normals.push_back(0.0f);
      normals.push_back(1.0f);
      normals.push_back(0.0f);

      normals.push_back(0.0f);
      normals.push_back(1.0f);
      normals.push_back(0.0f);

      normals.push_back(0.0f);
      normals.push_back(1.0f);
      normals.push_back(0.0f);

      // UVs
      uvs.push_back(0.0f); uvs.push_back(0.0f);
      uvs.push_back(0.0f); uvs.push_back(1.0f);
      uvs.push_back(1.0f); uvs.push_back(1.0f);
      uvs.push_back(0.0f); uvs.push_back(0.0f);
      uvs.push_back(0.0f); uvs.push_back(0.0f);
      uvs.push_back(1.0f); uvs.push_back(1.0f);

      currentIndex+=4;
    }
  }

  auto logger = Logger::Get("TerrainComponent");
  logger->info("Land generated. Vertices = {}, polygons = {}", vertices.size(), vertices.size() / 3);

  auto mesh = Engine::GetCurrentRenderSystem()->createMesh(std::move(vertices), std::move(uvs), std::move(normals));
  auto model = ModelManager::CreateFromMesh(std::move(mesh));

  Material defaultMaterial;
  defaultMaterial.color = Color::GRAY;

  model->getParts().at(0).material = data.material.value_or(defaultMaterial);
  return model;
}

std::shared_ptr<Terrain> FlatTerrainBuilder::build(const TerrainBuilder::Data &data) const {
  if (data.width * data.height * data.lod.getValue() == 0) {
    throw NotEnoughDataException();
  }

  auto model = makeModel(data);

  TerrainComponent::HeightMap heightMap;
  heightMap.resize(data.width);

  for (auto i = 0; i < data.width; i++) {
    heightMap[i].resize(data.height);
  }

  return std::make_shared<Terrain>(model, std::make_shared<TerrainComponent>(model, std::move(heightMap)));
}

}