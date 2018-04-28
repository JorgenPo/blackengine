//
// Created by popof on 25.04.2018.
//

#ifndef BLACKENGINE_BLACKMODELPARSER_H
#define BLACKENGINE_BLACKMODELPARSER_H

#include <core/parsers/ModelParser.h>
#include <iterator>

namespace black::parsers {
    /**
     * Parse fbx format
     *
     * FBX format parser v0.1
     */
    class FBXModelParser : public ModelParser {
        struct FBXHeader {
            std::string headerVersion;
            std::string versionString;
        };

        size_t numVertices;
        size_t numIndices;
        size_t numUVs;
        size_t numUVIndices;
        size_t numNormals;

        std::ifstream file;

        std::string textureName;
        std::string programName;
        int polygonLength;

        FBXHeader header;

        std::vector<float> *vertices;
        std::vector<unsigned int> *indices;
        std::vector<float> *uvs;

        std::vector<unsigned int> uvIndices;
    public:
        FBXModelParser *copy() const override;

        void parse(std::string file, std::vector<float> &vertices, std::vector<unsigned int> &indices,
                   std::vector<float> &textureCoords) override;

        int getPolygonLength() override;

        std::string getTextureName() override;

        std::string getProgramName() override;


    private:
        void readFBXHeader();
        void readVerticesBlock();
        void readIndicesBlock();
        void readTextureCoordsBlock();

        void readObjectsBlock();

        void readTextureCoordsIndicesBlock();

        void makeUVCoordinates();
    };
}


#endif //BLACKENGINE_BLACKMODELPARSER_H
