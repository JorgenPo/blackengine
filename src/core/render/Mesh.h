//
// Created by popof on 22.04.2018.
//

#ifndef BLACKENGINE_MESH_H
#define BLACKENGINE_MESH_H

#include <vector>
#include <cstdint>

namespace black::render {
    /**
     * Mesh is a vertices array
     */
    class Mesh {
    protected:
        std::vector<float> vertices;

    public:
        explicit Mesh(std::vector<float> vertices);

        int getVerticesCount();
        std::vector<float> getVertices();

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
