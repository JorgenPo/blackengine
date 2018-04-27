//
// Created by popof on 22.04.2018.
//

#ifndef BLACKENGINE_MESH_H
#define BLACKENGINE_MESH_H

#include <vector>
#include <cstdint>
#include <core/resources/Resource.h>
#include <memory>

namespace black::render {
    /**
     * Mesh is a vertices array
     */
    class Mesh {
    protected:
        std::vector<float> vertices;
        std::vector<float> textureCoords;
        std::vector<unsigned int> indices;

        int polygonLength;

        bool initialized;
    public:
        Mesh();
        explicit Mesh(std::vector<float> vertices, std::vector<unsigned int> indices,
                      std::vector<float> textureCoords, int polygonLength);

        int getVerticesCount();
        std::vector<float> getVertices();

        int getPolygonLength() const;

        void setPolygonLength(int polygonLength);

        const std::vector<unsigned int> &getIndices() const;
        int getIndicesCount();

        void setVertices(const std::vector<float> &vertices);

        void setTextureCoords(const std::vector<float> &textureCoords);

        void setIndices(const std::vector<unsigned int> &indices);

        bool isInitialized() const;

        /**
         * Bind a mesh. Makes it current.
         * Draw calls after bind must draw mesh data.
         */
        virtual void bind() = 0;

        /**
         * Unbinds a mesh. After this call render method
         * will not display a mesh vertices.
         */
        virtual void unbind() = 0;

        /**
         * Updates a buffer using current vertices
         * data.
         */
        virtual void update() = 0;
    };
}


#endif //BLACKENGINE_MESH_H
