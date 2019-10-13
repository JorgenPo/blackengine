//
// Created by popof on 26.09.2018.
//

#ifndef BLACKENGINE_SHAREDLIBRARY_H
#define BLACKENGINE_SHAREDLIBRARY_H

#include <exceptions/Exception.h>
#include <string>

namespace black {

/**
 * Function has not been found in library
 */
class FunctionNotFoundException : public Exception {
  std::string function;

public:
  /**
   * Constructor
   *
   * @param library Name of a library
   * @param function Function name
   */
  FunctionNotFoundException(std::string_view library, std::string_view function);

  /**
   * Returns a function name which cannot be found
   *
   * @return Function name string
   */
  const std::string &getFunction() const;
};

/**
 * Library has not been found
 */
class LibraryNotFoundException : public Exception {
public:
  /**
   * Constructor
   *
   * @param name A library name
   */
  explicit LibraryNotFoundException(std::string_view name);
};

class LibraryLoadingException : public Exception {
public:
  LibraryLoadingException(std::string_view name, std::string_view error);
};

/**
 * Abstract class for shared libraries (dll, so, ...)
 */
class AbstractSharedLibrary {
protected:
  std::string name;

public:
  /**
   * Constructor
   *
   * @param name Library name (without extension)
   */
  explicit AbstractSharedLibrary(std::string name);

  /**
   * Loads library
   *
   * @throws LibraryNotFoundException if no such library exist in searching path
   */
  virtual void load() = 0;

  /**
   * Free library
   */
  virtual void unload() = 0;

  /**
   * Returns function pointer in dll. If no such function then
   * exception will be thrown.
   *
   * @param name Name of function
   * @throws FunctionNotFoundException if function does not exist in library
   * @return pointer to the function
   */
  template<class T>
  T getFunction(const std::string &name);

private:
  /**
   * Internally return a function pointer for a given function name
   *
   * @param name Name of function
   * @throws FunctionNotFoundException if function does not exist in library
   * @return pointer to the function
   */
  virtual void *getFunctionPointer(std::string name) = 0;
};

template<class T>
T AbstractSharedLibrary::getFunction(const std::string &name) {
  return reinterpret_cast<T>(this->getFunctionPointer(name));
}
}

#endif //BLACKENGINE_SHAREDLIBRARY_H
