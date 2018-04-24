//
// Created by popof on 24.04.2018.
//

#ifndef BLACKENGINE_RESOURCE_H
#define BLACKENGINE_RESOURCE_H

namespace black::resources {
    /**
     * Abstract resource.
     * ! All resources must have a fromFile(std::string) static method !
     */
    class Resource {

    public:
        virtual ~Resource() = default;
    };
}


#endif //BLACKENGINE_RESOURCE_H
