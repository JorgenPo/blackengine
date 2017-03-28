#ifndef BLOBJPARSER_H
#define BLOBJPARSER_H

#include "src/core/blmesh.h"

#include <deque>
#include <vector>

#include <fstream>

namespace black {

/**
 * @brief The OBJParser class parses
 * a model from OBJ file format and produces
 * vectors of data such as positions, normals, indices and other.
 *
 * Check a file header and throws an exception if file given has a
 * wrong format.
 *
 * Probably needs some optimizations and benchmarking.
 *
 * @author george popoff <popoff96@live.com>
 *
 * @version 1.3.5 28.03.2017
 * Now reads information about material file.
 *
 * @version 1.3 26.03.2017
 * Fixed bug with texture coodinates. Now looks good.
 *
 * @version 1.2.5 22.03.2017
 * Fixed bug when object file contains multiple usemtl statements.
 *
 * @version 1.2 15.03.2017
 * Support for quad faces
 *
 * @version 1.1 15.03.2017
 * Support for obj files without texture coordinates
 *
 * @version 1.0 15.03.2017
 * Working version. maybe not too much fast.
 */
class OBJParser
{
public:
    OBJParser();

    /**
     * @brief Parses a obj file
     * @param file OBJ File path
     */
    void parse(std::string file);

    const std::vector<float>& positions() const { return m_vVertex; }
    const std::vector<float>& normals() const { return m_vNormal; }
    const std::vector<float>& texCoordinates() const { return m_vTexture; }
    const std::vector<uint>& indices() const { return m_vIndex; }

    size_t indicesCount() const { return m_vIndex.size(); }
    size_t verticesCount() const { return m_vVertex.size(); }

    bool hasTexture() const { return m_hasTexture; }
    bool quads() const { return m_quads; }

    std::string matFile() const;

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
    std::string m_matFile;

    std::ifstream m_file;

    bool m_hasTexture;
    bool m_quads;

};

}
#endif // BLOBJPARSER_H
