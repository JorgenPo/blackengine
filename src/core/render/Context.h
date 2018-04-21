//
// Created by popof on 20.04.2018.
//

#ifndef BLACKENGINE_CONTEXT_H
#define BLACKENGINE_CONTEXT_H

#include <core/Exception.h>

namespace black::render {

    class ContextInitializationException : public Exception {
    public:
        explicit ContextInitializationException(const std::string &message) : Exception(message) {}
    };

    /**
     * Represent a renderer context with all renderer objects.
     * Only one context can be current in one time
     */
    class Context {
    public:
        virtual void initializeContext() = 0;
        virtual void setContextCurrent() = 0;
        virtual bool isContextCurrent() = 0;
    };

}


#endif //BLACKENGINE_CONTEXT_H
