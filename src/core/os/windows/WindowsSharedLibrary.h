//
// Created by popof on 17.04.2018.
//

#ifndef BLACKENGINE_WINDOWSSHAREDLIBRARY_H
#define BLACKENGINE_WINDOWSSHAREDLIBRARY_H

#include <config/config.h>
#include <core/SharedLibrary.h>

#ifdef BLACK_PLATFORM_WINDOWS
#include <windows.h>
#endif

namespace black::os {

    /**
     * Windows shared library
     */
    class WindowsSharedLibrary : public SharedLibrary {
    private:
        HINSTANCE hLib;

    public:
        explicit WindowsSharedLibrary(std::string name);

        void load() override;
        void unload() override;

        void *getFunction(std::string name) override;
    };

}


#endif //BLACKENGINE_WINDOWSSHAREDLIBRARY_H
