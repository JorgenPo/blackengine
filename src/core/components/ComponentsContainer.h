//
// Created by popof on 23.04.2018.
//

#ifndef BLACKENGINE_COMPONENTSCONTAINER_H
#define BLACKENGINE_COMPONENTSCONTAINER_H

#include <string>
#include <map>
#include <memory>
#include <core/Exception.h>
#include <sstream>
#include "Component.h"

namespace black::components {

    class ComponentAlreadyExistException : public Exception {
    public:
        explicit ComponentAlreadyExistException(const std::string &name) : Exception() {
            std::stringstream stream;
            stream << "Component '" << name << "' already exist";
            this->message = stream.str();
        }
    };

    /**
     * Container for components
     */
    class ComponentsContainer {
        std::map<std::string, std::shared_ptr<Component>> components;

    public:
        /**
         * Returns a component with a given name or nullptr
         * if no component found or component type cast
         * failed.
         *
         * @tparam T Type of component to get
         *
         * @param name Name of component
         *
         * @return Requested component
         */
        template<typename T>
        std::shared_ptr<T> getComponent();

        /**
         * Add the component to container
         * @param name A name of component
         * @param component Component
         * @throws ComponentNameAlreadyExist If a given name is busy
         */
        template<typename T>
        void addComponent(const std::shared_ptr<T> &component);
    };

    template<typename T>
    std::shared_ptr<T> ComponentsContainer::getComponent() {
        if (this->components.find(T::getName()) == this->components.end()) {
            return nullptr;
        }

        return std::dynamic_pointer_cast<T>(this->components.at(T::getName()));
    }

    template<typename T>
    void ComponentsContainer::addComponent(const std::shared_ptr<T> &component) {
        if (this->components.find(T::getName()) != this->components.end()) {
            throw ComponentAlreadyExistException(T::getName());
        }

        this->components[T::getName()] = component;
    }

}


#endif //BLACKENGINE_COMPONENTSCONTAINER_H
