//
// Created by popof on 23.04.2018.
//

#ifndef BLACKENGINE_MODELCOMPONENT_H
#define BLACKENGINE_MODELCOMPONENT_H

#include <core/render/Mesh.h>
#include <memory>
#include "Component.h"

namespace black::components {
    /**
     * ModelComponent is holding mesh and
     * material data of object and can be rendered
     * by renderer
     */
    class Model : public Component, public resources::Resource {
        std::shared_ptr<render::Mesh> mesh;
        // TODO: material

    public:
        static std::shared_ptr<Model> fromFile(std::string fileName);

        static std::string getName() { return "Model"; }

        Model();

        explicit Model(const std::shared_ptr<render::Mesh> &mesh);

        const std::shared_ptr<render::Mesh> &getMesh() const;

        void setMesh(const std::shared_ptr<render::Mesh> &mesh);
    };

}


#endif //BLACKENGINE_MODELCOMPONENT_H
