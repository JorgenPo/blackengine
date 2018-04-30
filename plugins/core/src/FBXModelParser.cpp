//
// Created by popof on 25.04.2018.
//

#include <core/Core.h>
#include <cmath>
#include "FBXModelParser.h"

namespace black::parsers {
    FBXModelParser *FBXModelParser::copy() const {
        return new FBXModelParser();
    }

    void FBXModelParser::parse(std::string filename, std::vector<float> &vertices, std::vector<unsigned int> &indices,
                                 std::vector<float> &textureCoords) {
        this->vertices = &vertices;
        this->indices = &indices;
        this->uvs = &textureCoords;

        this->file = std::ifstream(filename);

        if (!file.is_open()) {
            throw ParseException("File stream not opened");
        }

        this->readFBXHeader();
        if (this->header.versionString.empty()) {
            throw WrongModelFormatException();
        }

        this->readPropertiesBlock();

        this->readObjectsBlock();

        this->makeUVCoordinates();

        this->readMaterials();

        auto rm = Core::getInstance()->getCurrentRenderer();
    }

    int FBXModelParser::getPolygonLength() {
        return this->polygonLength;
    }

    std::string FBXModelParser::getTextureName() {
        return this->textureName;
    }

    std::string FBXModelParser::getProgramName() {
        return this->programName;
    }

    /**
     * Reads vertices
     * @param values
     * @param predictedSize
     */
    void FBXModelParser::readVerticesBlock() {
        char separator; // ,
        float value;

        this->vertices->reserve(this->numVertices);

        for (int i = 0; i < this->numVertices; ++i) {
            this->file >> value >> separator;

            if (this->needFlip) {
                value = -value;
            }

            // When loading all models are flipped over
            this->vertices->push_back(value);
        }
    }

    void FBXModelParser::readIndicesBlock() {
        char separator;
        int value;
        int count = 0;
        this->indices->reserve(this->numIndices);

        for (int i = 0; i < this->numIndices; ++i) {
            count++;
            this->file >> value >> separator;

            // If value negative then this is the end of polygon
            // And actual index is 1 - indexVal
            if (value < 0) {
                if (this->polygonLength == 0) {
                    this->polygonLength = count;
                }

                value = abs(value) - 1;
            }

            this->indices->push_back(static_cast<unsigned int>(value));
        }
    }

    void FBXModelParser::readTextureCoordsIndicesBlock() {
        char separator;
        int value;

        this->uvIndices.reserve(this->numUVIndices);

        for (int i = 0; i < this->numUVIndices; ++i) {
            this->file >> value >> separator;
            this->uvIndices.push_back(static_cast<unsigned int>(value));
        }
    }

    void FBXModelParser::makeUVCoordinates() {
        char separator;
        float u = 0.0f;
        float v = 0.0f;

        std::vector<float> finalUVs(this->numVertices / 3 * 2);
        std::vector<int> usedVertices(this->numVertices / 3);

        size_t index;
        for (size_t i = 0; i < this->uvIndices.size(); i++) {
            u = this->uvs->at(this->uvIndices[i] * 2);
            v = this->uvs->at(this->uvIndices[i] * 2 + 1);

            index = this->indices->at(i);

            // Check if we wasn't already met that vertex (with index = indices[index))
            if (usedVertices.at(index) == 0)
            {
                finalUVs[index * 2] = abs(u);
                finalUVs[index * 2 + 1] = abs(v);
                usedVertices[index] = 1;
            } else if (finalUVs[index * 2] != u || finalUVs[index * 2 + 1] != v) { // We met that vertex, but different uvs used
                // There was already using of indices[index]th vertex,
                // so we have to duplicate this vertex
                this->vertices->push_back(this->vertices->at(index * 3));
                this->vertices->push_back(this->vertices->at(index * 3 + 1));
                this->vertices->push_back(this->vertices->at(index * 3 + 2));

                // Change index to point to new vertex (last pos)
                this->indices->at(i) = this->vertices->size() / 3 - 1;

                // Add new texture coordinate
                finalUVs.push_back(abs(u));
                finalUVs.push_back(abs(v));

                usedVertices.push_back(1);
            }
        }

        *(this->uvs) = finalUVs;
    }

    void FBXModelParser::readTextureCoordsBlock() {
        char separator;
        float value;

        this->uvs->reserve(this->numUVs);

        for (int i = 0; i < this->numUVs; ++i) {
            this->file >> value >> separator;
            this->uvs->push_back(value);
        }
    }

    void FBXModelParser::readFBXHeader() {
        std::string line;
        char c;
        while ((file >> line) && line != "FBXHeaderExtension:") {}

        file >> c; // { character
        file >> line; // FBXHeaderVersion
        file >> this->header.headerVersion;
        file >> line; // FBXVersion
        file >> this->header.versionString;
    }

    void FBXModelParser::readObjectsBlock() {
        std::string line;
        char c;

        // ORDER MATTERS
        static const std::vector<std::string> blocks {"Vertices:", "PolygonVertexIndex:",  "UV:", "UVIndex:", "Materials:"};
        std::map<std::string, size_t*> blockCounts {
                {"Vertices:", &(this->numVertices)},
                {"PolygonVertexIndex:", &(this->numIndices)},
                {"UV:", &(this->numUVs)},
                {"UVIndex:", &(this->numUVIndices)},
                {"Materials:", &(this->numMaterialOffsets)}
        };

        size_t count;

        // Read object blocks
        for (int i = 0; i < blocks.size(); i++) {
            while ((file >> line) && line != blocks[i]) {}
            file >> c; // * before vertices count or {

            if (c == '*') {
                file >> count;
                *blockCounts[blocks[i]] = count;
            }

            file >> c; // {
            file >> line; // a:

            if (blocks[i] == "Vertices:"){
                this->readVerticesBlock();
            } else if (blocks[i] == "PolygonVertexIndex:") {
                this->readIndicesBlock();
            } else if (blocks[i] == "UV:") {
                this->readTextureCoordsBlock();
            } else if (blocks[i] == "UVIndex:") {
                this->readTextureCoordsIndicesBlock();
            } else if (blocks[i] == "Materials:") {
                this->readMaterialOffsets();
            }
        }
    }

    render::MaterialList FBXModelParser::getMaterials() {
        return this->materialList;
    }

    std::vector<std::pair<int, int>> FBXModelParser::getMaterialOffsets() {
        return this->materialOffsets;
    }

    void FBXModelParser::readMaterials() {
        auto shader = Core::getInstance()->getResourceManager()
                ->load<render::ShaderProgram>("simple.shader");

        std::string line;
        for (int i = 0; i < this->materialList.size(); i++) {
            while ((file >> line) && line.find("Material::") == std::string::npos) {}
            // TODO: working with path
            size_t pos = line.find_last_of('\\') + 1;

            // Texture name with extension
            // minus double quotes and coma
            line = line.substr(pos, line.length() - pos - 2);

            auto material = std::make_shared<render::Material>(shader);
            try {
                material->setDiffuseTexture(line);
            } catch(const Exception &e) {
                // Just empty texture
            }

            this->materialList[i] = material;
        }
    }

    void FBXModelParser::readMaterialOffsets() {
        int maxMaterialIndex = 0;
        int index = -1;
        int oldIndex = 0;
        char separator;

        for (int i = 0; i < this->numMaterialOffsets; i++) {
            oldIndex = index;
            this->file >> index >> separator;

            // If material index has changed then
            // push offset to materialOffsets
            if (oldIndex != index) {
                this->materialOffsets.emplace_back(index, i * 3);
            }

            maxMaterialIndex = std::max(maxMaterialIndex, index);
        }

        this->materialList.resize(static_cast<unsigned int>(maxMaterialIndex) + 1);
    }

    void FBXModelParser::readPropertiesBlock() {
        std::string line;
        char c;
        int sign = 1;

        // Get up axis sign to avoid flipping of some models
        while ((file >> line) && line.find("UpAxisSign") == std::string::npos) {}

        //"int",
        file >> line;
        //"Integer", "",
        file >> line;

        //"",
        file >> c >> c >> c;

        file >> sign;

        this->needFlip = sign > 0;
    }
}
