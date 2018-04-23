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

    class ComponentNameAlreadyExistException : public Exception {
    public:
        explicit ComponentNameAlreadyExistException(const std::string &name) : Exception() {
            std::stringstream stream;
            stream << "Component with name '" << name << "' already exist";
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
        std::shared_ptr<T> getComponent(std::string name);

        /**
         * Add the component to container
         * @param name A name of component
         * @param component Component
         * @throws ComponentNameAlreadyExist If a given name is busy
         */
        void addComponent(const std::string &name, const std::shared_ptr<Component> &component) {
            if (this->components.find(name) != this->components.end()) {
                throw ComponentNameAlreadyExistException(name);
            }

            this->components[name] = component;
        }
    };

    template<typename T>
    std::shared_ptr<T> ComponentsContainer::getComponent(std::string name) {
        if (this->components.find(name) == this->components.end()) {
            return nullptr;
        }

        return std::dynamic_pointer_cast<T>(this->components.at(name));
    }

}


#endif //BLACKENGINE_COMPONENTSCONTAINER_H
