//
// Created by popof on 26.09.2018.
//

#ifndef BLACKENGINE_WINDOWSSHAREDLIBRARY_H
#define BLACKENGINE_WINDOWSSHAREDLIBRARY_H

#include "../../common/PlatformHeaders.h"
#include "../AbstractSharedLibrary.h"

namespace black::os {

    /**
     * Windows shared library (dll)
     */
    class WindowsSharedLibrary : public AbstractSharedLibrary {
    private:
        HINSTANCE hLib;

    public:
        /**
         * Constructor
         *
         * @param name Name of library without extension
         */
        explicit WindowsSharedLibrary(std::string name);

        void load() override;
        void unload() override;

        void *getFunctionPointer(std::string name) override;
    };

}


#endif //BLACKENGINE_WINDOWSSHAREDLIBRARY_H
