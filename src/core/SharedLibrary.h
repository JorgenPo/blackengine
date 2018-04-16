//
// Created by popof on 17.04.2018.
//

#ifndef BLACKENGINE_SHAREDLIBRARY_H
#define BLACKENGINE_SHAREDLIBRARY_H

#include <string>
#include "Exception.h"

namespace black {

    class FunctionNotFoundException : public Exception {
    public:
        FunctionNotFoundException(std::string library, std::string function);
    };

    class LibraryNotFoundException : public Exception {
    public:
        explicit LibraryNotFoundException(std::string name);
    };

    /**
     * Abstract class for shared libraries
     */
    class SharedLibrary {
    protected:
        std::string name;

    public:
        explicit SharedLibrary(std::string name);

        /**
         * Loads library
         *
         * @throws LibraryNotFoundException if no such library exist in searching path
         */
        virtual void load() = 0;

        virtual void unload() = 0;

        /**
         * Returns function pointer in dll. If no such function then
         * exception will be thrown.
         *
         * @param name Name of function
         * @throws FunctionNotFoundException if function does not exist in library
         * @return pointer to the function
         */
        virtual void* getFunction(std::string name) = 0;
    };
}

#endif //BLACKENGINE_SHAREDLIBRARY_H
