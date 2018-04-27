//
// Created by popof on 25.04.2018.
//

#ifndef BLACKENGINE_BLACKMODELPARSER_H
#define BLACKENGINE_BLACKMODELPARSER_H

#include <core/parsers/ModelParser.h>
#include <iterator>

namespace black::parsers {
    /**
     * Parse black model file format (bmf)
     *
     * BMF format v0.1
     */
    class BlackModelParser : public ModelParser {
        size_t numVertices;
        size_t numIndices;
        size_t numUVs;
        size_t numNormals;

        std::ifstream file;

        std::string textureName;
        std::string programName;
        int polygonLength;
    public:
        BlackModelParser *copy() const override;

        void parse(std::string file, std::vector<float> &vertices, std::vector<unsigned int> &indices,
                   std::vector<float> &textureCoords) override;

        int getPolygonLength() override;

        std::string getTextureName() override;

        std::string getProgramName() override;

    private:
        void readVerticesBlock(std::vector<float> &values, size_t predictedSize);
        void readIndicesBlock(std::vector<unsigned int> &values, size_t predictedSize);
        void readTextureCoordsBlock(std::vector<float> &values, std::vector<unsigned int> &indices, std::vector<float> &vertices);
    };
}


#endif //BLACKENGINE_BLACKMODELPARSER_H
