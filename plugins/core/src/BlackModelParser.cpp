//
// Created by popof on 25.04.2018.
//

#include <core/Core.h>
#include "BlackModelParser.h"

namespace black::parsers {
    BlackModelParser *BlackModelParser::copy() const {
        return new BlackModelParser();
    }

    void BlackModelParser::parse(std::string filename, std::vector<float> &vertices, std::vector<unsigned int> &indices,
                                 std::vector<float> &textureCoords) {
        this->file = std::ifstream(filename);

        if (!file.is_open()) {
            throw ParseException("File stream not opened");
        }

        if (!(file >> this->programName)) {
            throw WrongModelFormatException();
        }

        if (FileUtils::getFileExtension(this->programName).empty()) {
            throw Exception("Program must be set");
        }

        if (!(file >> this->textureName)) {
            throw WrongModelFormatException();
        }

        if (FileUtils::getFileExtension(this->textureName).empty()) {
            throw Exception("Texture must be set");
        }

        if (!(file >> this->numVertices)) {
            throw WrongModelFormatException();
        }
        if (!(file >> this->numIndices)) {
            throw WrongModelFormatException();
        }
        if (!(file >> this->numUVs)) {
            throw WrongModelFormatException();
        }
        if (!(file >> this->numNormals)) {
            throw WrongModelFormatException();
        }

        this->readVerticesBlock(vertices, numVertices);
        this->readIndicesBlock(indices, numIndices);

        textureCoords.resize(vertices.size() / 3 * 2);
        this->readTextureCoordsBlock(textureCoords, indices, vertices);

        auto rm = Core::getInstance()->getCurrentRenderer();
    }

    int BlackModelParser::getPolygonLength() {
        return this->polygonLength;
    }

    std::string BlackModelParser::getTextureName() {
        return this->textureName;
    }

    std::string BlackModelParser::getProgramName() {
        return this->programName;
    }

    void BlackModelParser::readVerticesBlock(std::vector<float> &values, size_t predictedSize) {
        char separator;
        float value;
        values.reserve(predictedSize);

        if (!(file >> separator)) {
            throw WrongModelFormatException();
        } else if (separator != '{') {
            throw WrongModelFormatException();
        }

        while ( this->file >> value >> separator && separator != '}' ) {
            values.push_back(value);
        }

        // The last element
        values.push_back(value);
    }

    void BlackModelParser::readIndicesBlock(std::vector<unsigned int> &values, size_t predictedSize) {
        char separator;
        int value;
        int count = 0;
        values.reserve(predictedSize);

        if (!(file >> separator)) {
            throw WrongModelFormatException();
        } else if (separator != '{') {
            throw WrongModelFormatException();
        }

        while ( this->file >> value >> separator && separator != '}' ) {
            count++;

            // If value negative then this is the end of polygon
            // And actual index is 1 - indexVal
            if (value < 0) {
                if (this->polygonLength == 0) {
                    this->polygonLength = count;
                }

                value = abs(value) - 1;
            }

            values.push_back(static_cast<unsigned int>(value));
        }

        // The last index (negative)
        values.push_back(static_cast<unsigned int>(abs(value)) - 1);
    }

    void BlackModelParser::readTextureCoordsBlock(std::vector<float> &values, std::vector<unsigned int> &indices,
                                                  std::vector<float> &vertices) {
        char separator;
        int index = 0;
        float u = 0.0f;
        float v = 0.0f;

        if (!(file >> separator)) {
            throw WrongModelFormatException();
        } else if (separator != '{') {
            throw WrongModelFormatException();
        }

        std::vector<int> usedVertices(values.size() / 2);

        while ( this->file >> u >> separator >> v >> separator && separator != '}' ) {
            // Check if we wasn't already met that vertex (with index = indices[index))
            if (usedVertices[indices[index]] == 0)
            {
                values[indices[index] * 2] = abs(u);
                values[indices[index] * 2 + 1] = abs(v);
                usedVertices[indices[index]] = 1;
            } else if (values[indices[index] * 2] != u || values[indices[index] * 2 + 1] != v) { // We met that vertex, but different uvs used
                // There was already using of indices[index]th vertex,
                // so we have to duplicate this vertex
                vertices.push_back(vertices[indices[index] * 3]);
                vertices.push_back(vertices[indices[index] * 3 + 1]);
                vertices.push_back(vertices[indices[index] * 3 + 2]);

                // Change index to point to new vertex (last pos)
                indices[index] = vertices.size() / 3 - 1;

                // Add new texture coordinate
                values.push_back(abs(u));
                values.push_back(abs(v));

                usedVertices.push_back(1);
            }
            index++;
        }

        if (usedVertices[indices[index]] == 0) {
            values[indices[index] * 2] = abs(u);
            values[indices[index] * 2 + 1] = abs(v);
        } else if (values[indices[index] * 2] != u || values[indices[index] * 2 + 1] != v) {
            // TODO: Refactor all this code.

            vertices.push_back(vertices[indices[index] * 3]);
            vertices.push_back(vertices[indices[index] * 3 + 1]);
            vertices.push_back(vertices[indices[index] * 3 + 2]);

            indices[index] = vertices.size() / 3 - 1;

            values.push_back(abs(u));
            values.push_back(abs(v));
        }
    }
}
