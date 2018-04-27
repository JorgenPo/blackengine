//
// Created by popof on 23.04.2018.
//

#ifndef BLACKENGINE_MODELCOMPONENT_H
#define BLACKENGINE_MODELCOMPONENT_H

#include <core/render/Mesh.h>
#include <memory>
#include <core/render/Material.h>
#include "core/components/Component.h"

namespace black::render {
    /**
     * ModelComponent is holding mesh and
     * material data of object and can be rendered
     * by renderer
     */
    class Model : public components::Component, public resources::Resource {
        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<Material> material;

    public:
        static std::shared_ptr<Model> fromFile(std::string fileName);

        static std::string getName() { return "Model"; }

        Model(const std::shared_ptr<Mesh> &mesh, const std::shared_ptr<Material> &material);

        const std::shared_ptr<Mesh> &getMesh() const;

        void setMesh(const std::shared_ptr<Mesh> &mesh);

        const std::shared_ptr<Material> &getMaterial() const;

        void setMaterial(const std::shared_ptr<Material> &material);
    };

}


#endif //BLACKENGINE_MODELCOMPONENT_H
