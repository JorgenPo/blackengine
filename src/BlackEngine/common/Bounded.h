//
// Created by popov on 24.07.2019.
//

#ifndef BLACKENGINE_BOUNDED_H
#define BLACKENGINE_BOUNDED_H

#include "Exported.h"

#include <memory>
#include <algorithm>

namespace black {

/**
 * Bounded - is a type wrapper with min and max values.
 * The real value will be clipped to the bounds.
 */
template<typename T, int min, int max>
class BLACK_EXPORTED Bounded {
  T value;

public:
  explicit Bounded(const T &value);

  void setValue(const T &value);

  const T &getValue() const;

  T &getValue();

  Bounded &operator=(const T &value);

  const T &operator*();
};

template<typename T, int min, int max>
Bounded<T, min, max>::Bounded(const T &value) : value(value) {

}

template<typename T, int min, int max>
void Bounded<T, min, max>::setValue(const T &newValue) {
  value = newValue;
}

template<typename T, int min, int max>
const T &Bounded<T, min, max>::getValue() const {
  return value;
}

template<typename T, int min, int max>
T &Bounded<T, min, max>::getValue() {
  return value;
}

template<typename T, int min, int max>
Bounded<T, min, max> &Bounded<T, min, max>::operator=(const T &newValue) {
  setValue(newValue);
  return *this;
}

template<typename T, int min, int max>
const T &Bounded<T, min, max>::operator*() {
  return value;
}

}

#endif //BLACKENGINE_BOUNDED_H
