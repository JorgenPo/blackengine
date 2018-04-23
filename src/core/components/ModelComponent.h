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
    class ModelComponent : public Component {
        std::shared_ptr<render::Mesh> mesh;
        // TODO: material

    public:
        ModelComponent();

        explicit ModelComponent(const std::shared_ptr<render::Mesh> &mesh);

        const std::shared_ptr<render::Mesh> &getMesh() const;

        void setMesh(const std::shared_ptr<render::Mesh> &mesh);
    };

}


#endif //BLACKENGINE_MODELCOMPONENT_H
