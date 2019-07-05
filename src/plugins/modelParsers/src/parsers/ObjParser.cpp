//
// Created by popof on 05.11.2018.
//

#include "ObjParser.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobj/tiny_obj_loader.h>

#include <Engine.h>
#include <Image.h>
#include <render/Material.h>
#include <render/RenderSystemInterface.h>

#include <log/Logger.h>
#include <components/ModelComponent.h>

namespace black {
ObjParser::ObjParser() : isObjParsed(false) {}

void ObjParser::parse(std::string file) {
  auto logger = Logger::Get("ObjParser");

  tinyobj::attrib_t attributes;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  std::string error;

  bool isParsed = false;
  isParsed = tinyobj::LoadObj(&attributes, &shapes, &materials, &error, file.c_str());

  if (isParsed && !error.empty()) {
    logger->warning("Parsing '{0}' warnings:\n {1}", file, error);
  }

  if (!isParsed) {
    logger->error("Loading '{0}' error: {1}", file, error);
    throw ParseException(file, error);
  }

  auto rs = Engine::GetCurrentRenderSystem();
  auto defaultMaterial = std::make_shared<Material>();
  auto modelParts = std::vector<ModelPart>();

  // Iterate over shapes (model parts)
  for (int i = 0; i < shapes.size(); i++) {
    const auto &shape = shapes[i];

    auto vertices = std::vector<float>();
    auto textureCoords = std::vector<float>();
    auto normals = std::vector<float>();

    vertices.reserve(shape.mesh.indices.size());
    textureCoords.reserve(shape.mesh.indices.size());
    normals.reserve(shape.mesh.indices.size());

    size_t indexOffset = 0;

    // Iterate over faces
    for (auto &faceSize : shape.mesh.num_face_vertices) {
      // Iterate over vertices in face
      for (size_t index = 0; index < faceSize; ++index) {
        auto idx = shape.mesh.indices[index + indexOffset];

        vertices.push_back(attributes.vertices[3 * idx.vertex_index + 0]);   // vx
        vertices.push_back(attributes.vertices[3 * idx.vertex_index + 1]);   // vy
        vertices.push_back(attributes.vertices[3 * idx.vertex_index + 2]);   // vz
        textureCoords.push_back(attributes.texcoords[2 * idx.texcoord_index + 0]);   // tx
        textureCoords.push_back(attributes.texcoords[2 * idx.texcoord_index + 1]);   // ty
        normals.push_back(attributes.normals[3 * idx.normal_index + 0]);   // vx
        normals.push_back(attributes.normals[3 * idx.normal_index + 1]);   // vy
        normals.push_back(attributes.normals[3 * idx.normal_index + 2]);   // vz
      }
      indexOffset += faceSize;
    }

    auto material = defaultMaterial;
    try {
      // Get first face material as entire object material
      // This is correct for most cases
      auto mat = materials.at(shape.mesh.material_ids[0]);

      if (mat.diffuse_texname.empty()) {
        material = std::make_shared<Material>(
            Color(mat.diffuse[0], mat.diffuse[1], mat.diffuse[2], 1.0f));
      } else {
        auto image = std::make_shared<Image>(mat.diffuse_texname, true);
        auto texture = rs->createTexture(
            image,
            true,
            TextureFiltering::NEAREST,
            TextureWrapping::CLAMP_TO_EDGE);

        material = std::make_shared<Material>(std::move(texture));
      }
    } catch (const std::out_of_range &e) {
      // default material
    } catch (const FileNotFoundException &e) {
      logger->warning("Failed to load model material: {0}", e.getMessage());
      // default material
    }

    auto mesh = rs->createMesh(
        std::move(vertices), std::move(textureCoords), std::move(normals));

    modelParts.emplace_back(shape.name, std::move(mesh), std::move(material));
  }

  this->model = std::make_shared<ModelComponent>(modelParts);
  this->isObjParsed = true;
}

bool ObjParser::isParsed() {
  return isObjParsed;
}

std::shared_ptr<ModelComponent> ObjParser::getModel() {
  return this->model;
}

std::shared_ptr<ModelParser> ObjParser::copy() {
  return std::shared_ptr<ModelParser>(new ObjParser());
}
}