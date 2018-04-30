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
        size_t numMaterialOffsets;

        std::ifstream file;

        std::string textureName;
        std::string programName;
        int polygonLength;

        FBXHeader header;

        std::vector<float> *vertices;
        std::vector<unsigned int> *indices;
        std::vector<float> *uvs;
        std::vector<unsigned int> uvIndices;

        render::MaterialList materialList;
        std::vector<std::pair<int, int>> materialOffsets;

        int needFlip;
    public:
        FBXModelParser *copy() const override;

        void parse(std::string file, std::vector<float> &vertices, std::vector<unsigned int> &indices,
                   std::vector<float> &textureCoords) override;

        int getPolygonLength() override;

        std::string getTextureName() override;

        std::string getProgramName() override;

        render::MaterialList getMaterials() override;

        std::vector<std::pair<int, int>> getMaterialOffsets() override;

    private:
        void readFBXHeader();
        void readVerticesBlock();
        void readIndicesBlock();
        void readTextureCoordsBlock();

        void readObjectsBlock();

        void readTextureCoordsIndicesBlock();

        void makeUVCoordinates();

        void readMaterials();

        void readMaterialOffsets();

        void readPropertiesBlock();
    };
}


#endif //BLACKENGINE_BLACKMODELPARSER_H
