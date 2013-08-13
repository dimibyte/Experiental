///The Singleton will come in useful for many key engine systems, such as the kernel or settings manager, of which we only ever want one.

#include "singleton.h"

template <typename T> T* Singleton <T>::ms_singleton = 0;
