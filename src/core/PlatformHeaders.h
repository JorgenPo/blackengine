//
// Created by popof on 26.09.2018.
//

#ifndef BLACKENGINE_PLATFORMHEADERS_H
#define BLACKENGINE_PLATFORMHEADERS_H

#include <Config.h>

#if defined(BLACK_PLATFORM_WINDOWS)
    #include <windows.h>
#elif defined(BLACK_PLATFORM_LINUX)
    #include <dlfcn.h>
#endif

#endif //BLACKENGINE_PLATFORMHEADERS_H
