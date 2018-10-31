//
// Created by popof on 24.09.2018.
//

#ifndef BLACKENGINE_COMMONHEADERS_H
#define BLACKENGINE_COMMONHEADERS_H

#include <Exported.h>
#include <Config.h>
#include <exceptions/Exception.h>

// Threading

//#ifdef BLACK_COMPILER_MINGW
//
//// Without this it is not working!
//#include <mingw.thread.h>
//#include <mingw.mutex.h>
//#include <mingw.condition_variable.h>
//#include <mingw.shared_mutex.h>
//#include <mingw.future.h>
//
//#else // NOT MINGW
//#include <thread>
//#include <future>
//#endif

// Common std library includes
#include <string>
#include <memory>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

#include <PlatformHeaders.h>

#include <Constants.h>

#include <exceptions/Exception.h>

#include <Types.h>

#include <log/Logger.h>
#include <performance/PerformanceCounter.h>
#include <Copyable.h>

#include <util/Strings.h>
#include <util/Paths.h>

// Matrices
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#endif //BLACKENGINE_COMMONHEADERS_H
