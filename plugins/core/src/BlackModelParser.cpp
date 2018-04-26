//
// Created by popof on 25.04.2018.
//

#include <core/Core.h>
#include "BlackModelParser.h"

namespace black::parsers {
    BlackModelParser *BlackModelParser::copy() const {
        return new BlackModelParser();
    }

    template<typename T>
    void BlackModelParser::readBlock(std::vector<T> &values, size_t predictedSize) {
        char separator;
        T value;
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

    void BlackModelParser::parse(std::string filename, std::vector<float> &vertices, std::vector<unsigned int> &indices,
                                 std::vector<float> &textureCoords) {
        this->file = std::ifstream(filename);

        if (!file.is_open()) {
            throw ParseException("File stream not opened");
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

        this->readBlock<float>(vertices, numVertices);
        this->readIndicesBlock(indices, numIndices);
        this->readBlock<float>(textureCoords, numUVs);

        auto rm = Core::getInstance()->getCurrentRenderer();
    }

    int BlackModelParser::getPolygonLength() {
        return this->polygonLength;
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

    std::string BlackModelParser::getTextureName() {
        return this->textureName;
    }
}
