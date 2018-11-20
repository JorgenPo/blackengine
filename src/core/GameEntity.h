//
// Created by popof on 19.04.2018.
//

#ifndef BLACKENGINE_OBJECT_H
#define BLACKENGINE_OBJECT_H

#include <CommonHeaders.h>

#include <components/ComponentsContainer.h>
#include <components/TransformComponent.h>

namespace black {

    class GameEntity;

    using GameEntityVector = std::vector<std::shared_ptr<GameEntity>>;

    /**
     * Game entity object
     */
    class BLACK_EXPORTED GameEntity : public ComponentsContainer, public std::enable_shared_from_this<GameEntity> {
        static long long int idCounter;

        std::string name;

    public:
        std::shared_ptr<TransformComponent> transform;

        /**
         * Creates an empty entity with only transform component
         */
        explicit GameEntity(std::string name = "");
        virtual ~GameEntity();

        const std::string &getName() const;
        void setName(const std::string &name);
    };
}


#endif //BLACKENGINE_OBJECT_H
