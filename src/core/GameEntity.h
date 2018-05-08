//
// Created by popof on 19.04.2018.
//

#ifndef BLACKENGINE_OBJECT_H
#define BLACKENGINE_OBJECT_H

#include <list>
#include <memory>
#include <core/components/ComponentsContainer.h>
#include <core/components/TransformComponent.h>

namespace black {

    class GameEntity;

    using GameEntityList = std::list<std::shared_ptr<GameEntity>>;

    /**
     * Game entity object
     */
    class GameEntity : public components::ComponentsContainer {
        std::string name;
        std::shared_ptr<GameEntity> parent;
        GameEntityList children;

    public:
        std::shared_ptr<components::TransformComponent> transform;

        /**
         * Creates an empty entity with only transform component
         */
        explicit GameEntity(std::string name = "");

        /**
         * Creates an empty entity with only transform component
         * and set's it position to position
         *
         * @param position New position
         */
        explicit GameEntity(std::array<float, 3> position);

        /**
         * Creates an empty entity with given parent
         * @param parent
         */
        explicit GameEntity(std::shared_ptr<GameEntity> parent);

        virtual ~GameEntity();

        void attachChild(std::shared_ptr<GameEntity> child);
        void detachChild(std::shared_ptr<GameEntity> child);

        const std::string &getName() const;

        void setName(const std::string &name);

        const std::shared_ptr<GameEntity> &getParent() const;

        void setParent(const std::shared_ptr<GameEntity> &parent);

        const GameEntityList &getChildren() const;
    };
}


#endif //BLACKENGINE_OBJECT_H
