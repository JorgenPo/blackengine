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
    class Mesh : public resources::Resource {
    protected:
        std::vector<float> vertices;
        std::vector<float> textureCoords;
        std::vector<unsigned int> indices;

    public:
        static std::shared_ptr<Mesh> fromFile(std::string filename);

        explicit Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> textureCoords);

        int getVerticesCount();
        std::vector<float> getVertices();

        const std::vector<unsigned int> &getIndices() const;
        int getIndicesCount();

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
