#include "blobjparser.h"

#include <blfileexceptions.h>
#include <iostream>

namespace black {

OBJParser::OBJParser()
    : m_vertices(),
      m_normals(),
      m_uvCoords(),
      m_indices(),

      m_vVertex(),
      m_vNormal(),
      m_vTexture(),
      m_vIndex(),
      m_matFile(),

      m_file(),

      m_hasTexture(true),
      m_quads(false)
{

}

void OBJParser::parse(std::string path)
{
    m_file.open(path);
    if ( !m_file.is_open() ) {
        throw NoSuchFileException(path);
    }

    std::string line;

    std::string header1;
    getline(m_file, header1); // First header line

    std::string header2;
    getline(m_file, header2); // Second header line

    if ( header1.find("OBJ") == std::string::npos ) {
        throw WrongFileException(path, ".obj");
    }

    std::string type; // Type of a data (v for vertices, vn for normals and so on)

    /* Reads verices and indices data until line with starting f*/
    try {
        while (readVertex()) {}
    } catch(std::exception &e) {
        throw ParseException(path, e.what());
    }

    // Sorting data
    m_vVertex.reserve(m_vertices.size());
    m_vNormal.reserve(m_normals.size());
    m_vTexture.reserve(m_uvCoords.size());
    m_vIndex.reserve(m_indices.size());

    if ( m_uvCoords.size() == 0 ) {
        m_hasTexture = false;
    }

    while (true) {
       if ( !readFace() ) {
           break;
       }
    }

    m_file.close();
}

void OBJParser::splitString(std::string str, std::string delimiter, std::string *out, int size)
{
    int count = 0;
    size_t pos = str.find(delimiter);
    std::string token;
    do {
        if ( ++count > size ) {
            return;
        }

        token = str.substr(0, pos);

        *(out) = token;
        ++out;

        str.erase(0, pos + delimiter.length());
    } while ( (pos = str.find(delimiter)) != std::string::npos );

    *(out) = str;
}

bool OBJParser::readVertex()
{
    std::string type;
    try {
        m_file >> type;

        if ( type == "v" ) {
            readCoord();
        } else if ( type == "vt" ) {
            readTexture();
        } else if ( type == "vn" ) {
            readNormal();
        } else if ( type == "f" ) {   // End of list
            m_file.unget();
            return false;
        } else if ( type == "mtllib" ) {
            m_file >> m_matFile;
        } else { // Skip this line
            getline(m_file, type);
            return true;
        }

        return true;
    } catch(std::exception &e) {
        throw e;
    }
}

void OBJParser::readCoord()
{
    float fnumber;

    m_file >> fnumber;
    m_vertices.push_back(fnumber);
    m_file >> fnumber;
    m_vertices.push_back(fnumber);
    m_file >> fnumber;
    m_vertices.push_back(fnumber);
}

void OBJParser::readTexture()
{
    float fnumber;

    // 1.0f - fnumber on y fix 26.03.17
    // blender texture starts on bottom left
    // opengl texture starts on top left
    m_file >> fnumber;
    m_uvCoords.push_back(fnumber);
    m_file >> fnumber;
    m_uvCoords.push_back(1.0f - fnumber);
}

void OBJParser::readNormal()
{
    float fnumber;

    m_file >> fnumber;
    m_normals.push_back(fnumber);
    m_file >> fnumber;
    m_normals.push_back(fnumber);
    m_file >> fnumber;
    m_normals.push_back(fnumber);
}

void OBJParser::readIndex()
{
    int inumber;

    m_file >> inumber;
    m_indices.push_back(inumber);
    m_file >> inumber;
    m_indices.push_back(inumber);
}

bool OBJParser::readFace()
{
    std::string type;
    std::string group;
    std::string splited[4];

    m_file >> type;

    if ( type.empty() ) {
        return false;
    }

    if ( type != "f" ) {
        getline(m_file, type); // seek to the end of line
        return true;
    }

    int i = 0;
    std::string delimiter = m_hasTexture ? "/" : "//";
    for (i = 0; i < 4; ++i) {

        // x\y\z group
        if ( !(m_file >> group) ) {
            break;
        }

        if ( group == "f" || group == "usemtl" ) {
            m_file.unget();
            break;
        }

        splitString(group, delimiter, splited, 3);

        readFaceElement(splited);
    }

    if ( i == 4 ) {
        m_quads = true;
    }

    return true;
}

void OBJParser::readFaceElement(const std::string splited[])
{
    int index = std::stoi(splited[0]) - 1;

    m_vVertex.push_back(m_vertices[index * 3]);
    m_vVertex.push_back(m_vertices[index * 3 + 1]);
    m_vVertex.push_back(m_vertices[index * 3 + 2]);

    if ( m_hasTexture ) {
        index = std::stoi(splited[1]) - 1;
        m_vTexture.push_back(m_uvCoords[index * 2]);
        m_vTexture.push_back(m_uvCoords[index * 2 + 1]);

        index = std::stoi(splited[2]) - 1;
    } else { // If there are no texture coord (1//1)
        index = std::stoi(splited[1]) - 1;
    }

    m_vNormal.push_back(m_normals[index * 3]);
    m_vNormal.push_back(m_normals[index * 3 + 1]);
    m_vNormal.push_back(m_normals[index * 3 + 2]);
}

std::string OBJParser::matFile() const
{
    return m_matFile;
}

}
