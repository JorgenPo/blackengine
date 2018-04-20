//
// Created by popof on 20.04.2018.
//

#ifndef BLACKENGINE_CONTEXT_H
#define BLACKENGINE_CONTEXT_H

namespace black::render {

    /**
     * Represent a renderer context with all renderer objects.
     * Only one context can be current in one time
     */
    class Context {
    public:
        virtual void setContextCurrent() = 0;
        virtual bool isContextCurrent() = 0;
    };

}


#endif //BLACKENGINE_CONTEXT_H
