//
// Created by popof on 05.11.2018.
//

#include "ObjParser.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobj/tiny_obj_loader.h>

#include <Engine.h>

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

        auto defaultMaterial = std::make_shared<Material>();

        auto modelParts = std::vector<ModelPart>();

        // Iterate over shapes (model parts)
        for (auto &shape : shapes) {
            auto vertices = std::vector<float>();
            auto textureCoords = std::vector<float>();
            vertices.reserve(shape.mesh.indices.size());
            textureCoords.reserve(shape.mesh.indices.size());

            size_t indexOffset = 0;

            // Iterate over faces
            for (auto &faceSize : shape.mesh.num_face_vertices) {
                // Iterate over vertices in face
                for (size_t index = 0; index < faceSize; ++index) {
                    auto idx = shape.mesh.indices[index + indexOffset];

                    vertices.push_back(attributes.vertices[3*idx.vertex_index+0]);   // vx
                    vertices.push_back(attributes.vertices[3*idx.vertex_index+1]);   // vy
                    vertices.push_back(attributes.vertices[3*idx.vertex_index+2]);   // vz
                    textureCoords.push_back(attributes.texcoords[2*idx.texcoord_index+0]);   // tx
                    textureCoords.push_back(attributes.texcoords[2*idx.texcoord_index+1]);   // ty

                }
                indexOffset += faceSize;
            }

            auto mesh = Engine::GetCurrentRenderSystem()->createMesh(vertices, textureCoords);
            modelParts.emplace_back(shape.name, mesh, defaultMaterial);
        }

        this->model = std::make_shared<Model>(modelParts);
        this->isObjParsed = true;
    }

    bool ObjParser::isParsed() {
        return isObjParsed;
    }

    std::shared_ptr<Model> ObjParser::getModel() {
        return this->model;
    }

    std::shared_ptr<ModelParser> ObjParser::copy() {
        return std::shared_ptr<ModelParser>(new ObjParser());
    }
}