//
// Created by popof on 28.10.2018.
//

#ifndef BLACKENGINE_MODEL_H
#define BLACKENGINE_MODEL_H

#include <CommonHeaders.h>
#include <Mesh.h>
#include <Material.h>

namespace black {

    class BLACK_EXPORTED ModelPartNotFoundException : public Exception {
    public:
        explicit ModelPartNotFoundException(std::string partName);
    };

    /**
     * Part of a model. One mesh and material with a name.
     */
    struct BLACK_EXPORTED ModelPart {
        std::string name;
        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<Material> material;

        ModelPart(const std::string &name, const std::shared_ptr<Mesh> &mesh,
                  const std::shared_ptr<Material> &material);
    };

    /**
     * One or more meshes with some material each
     */
    class BLACK_EXPORTED Model {
        std::vector<ModelPart> parts;

    public:
        /**
         * Construct a model from model parts
         */
        explicit Model(std::vector<ModelPart> parts);

        /**
         * Return a list of the model parts
         *
         * @return List of model parts
         */
        const std::vector<ModelPart> &getParts() const;

        /**
         * Get the model part with a specific name.
         *
         * @param name Name of the model part
         * @return Part of the model corresponding a given name
         * @throws ModelPartNotFoundException If ModelPart with a given name has not been found
         */
        const ModelPart &getPart(std::string name);
    };

}
#endif //BLACKENGINE_MODEL_H
