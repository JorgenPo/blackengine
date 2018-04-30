//
// Created by popof on 23.04.2018.
//

#ifndef BLACKENGINE_MODELCOMPONENT_H
#define BLACKENGINE_MODELCOMPONENT_H

#include <core/render/Mesh.h>
#include <memory>
#include <list>
#include <core/render/Material.h>
#include "core/components/Component.h"

namespace black::render {
    using MaterialList = std::vector<std::shared_ptr<Material>>;

    /**
     * ModelComponent is holding mesh and
     * material data of object and can be rendered
     * by renderer
     */
    class Model : public components::Component, public resources::Resource {
        std::shared_ptr<Mesh> mesh;
        MaterialList materials;
        std::vector<std::pair<int, int>> materialOffsets;

    public:
        static std::shared_ptr<Model> fromFile(std::string fileName);

        static std::string getName() { return "Model"; }

        Model(std::shared_ptr<Mesh> mesh, const MaterialList &materials, const std::vector<std::pair<int, int>> &materialOffsets);

        const std::shared_ptr<Mesh> &getMesh() const;

        void setMesh(const std::shared_ptr<Mesh> &mesh);

        const MaterialList &getMaterials() const;

        void setMaterials(const MaterialList &materials);

        /**
         * Draws model
         */
        void render();
    };

}


#endif //BLACKENGINE_MODELCOMPONENT_H
