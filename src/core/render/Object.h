//
// Created by popof on 19.04.2018.
//

#ifndef BLACKENGINE_OBJECT_H
#define BLACKENGINE_OBJECT_H

#include <list>
#include <memory>

namespace black::render {

    /**
     * Object that can be rendered and moved
     */
    class Object {

    };

    using ObjectList = std::list<std::shared_ptr<Object>>;
}


#endif //BLACKENGINE_OBJECT_H
