//
// Created by popof on 26.09.2018.
//

#include "WindowsSharedLibrary.h"
#include <log/Logger.h>

namespace black::os {

    void WindowsSharedLibrary::load() {
        std::string name = this->name + ".dll";

        this->hLib = LoadLibrary(TEXT(name.c_str()));

        if (this->hLib == nullptr) {
            DWORD error = GetLastError();
            throw LibraryNotFoundException(name);
        }
    }

    void WindowsSharedLibrary::unload() {
        // This will cause sig fault
        FreeLibrary(this->hLib);
    }

    WindowsSharedLibrary::WindowsSharedLibrary(std::string name) :
            AbstractSharedLibrary(std::move(name)), hLib()
    {

    }

    void *WindowsSharedLibrary::getFunctionPointer(std::string name) {
        if (this->hLib == nullptr) {
            return nullptr;
        }

        auto function = reinterpret_cast<void*>(GetProcAddress(this->hLib, name.c_str()));

        if (function == nullptr) {
            throw FunctionNotFoundException(this->name + ".dll", name);
        }

        return function;
    }
}