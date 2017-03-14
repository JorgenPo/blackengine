#ifndef BLOBJPARSER_H
#define BLOBJPARSER_H

#include "src/core/blmesh.h"

#include <deque>
#include <vector>

#include <fstream>

namespace black {

class OBJParser
{
public:
    OBJParser();

    void parseObj(std::string file);

    const std::vector<float>& positions() const { return m_vVertex; }
    const std::vector<float>& normals() const { return m_vNormal; }
    const std::vector<float>& texCoordinates() const { return m_vTexture; }
    const std::vector<uint>& indices() const { return m_vIndex; }

    size_t indicesCount() const { return m_vIndex.size(); }
    size_t verticesCount() const { return m_vVertex.size(); }

private:
    void splitString(std::string str, std::string delimiter, std::string *out, int size);

    bool readVertex();

    void readCoord();
    void readTexture();
    void readNormal();
    void readIndex();

    bool readFace();
    void readFaceElement(const std::string splited[]);

private:

    // INPUT
    std::deque<float> m_vertices;
    std::deque<float> m_normals;
    std::deque<float> m_uvCoords;
    std::deque<int>   m_indices;

    // RESULT
    std::vector<float> m_vVertex;
    std::vector<float> m_vNormal;
    std::vector<float> m_vTexture;
    std::vector<uint>  m_vIndex;

    std::ifstream m_file;
};

}
#endif // BLOBJPARSER_H
