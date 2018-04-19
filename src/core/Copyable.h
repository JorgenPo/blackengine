//
// Created by popof on 19.04.2018.
//

#ifndef BLACKENGINE_COPYABLE_H
#define BLACKENGINE_COPYABLE_H

#include <memory>

namespace black {
    /**
     * A object that able to copy itself
     */
    class Copyable {
    public:
        virtual Copyable *copy() const = 0;
    };
}


#endif //BLACKENGINE_COPYABLE_H
