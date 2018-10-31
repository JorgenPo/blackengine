//
// Created by popof on 19.04.2018.
//

#ifndef BLACKENGINE_COPYABLE_H
#define BLACKENGINE_COPYABLE_H

#include <Exported.h>
#include <memory>

namespace black {
    /**
     * Copyable object interface
     */
    class BLACK_EXPORTED Copyable {
    public:
        virtual std::shared_ptr<Copyable> copy() const = 0;
    };
}


#endif //BLACKENGINE_COPYABLE_H
