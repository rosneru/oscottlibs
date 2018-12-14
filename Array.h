#ifndef OSCOTTLIBS_ARRAY_H_
#define OSCOTTLIBS_ARRAY_H_

#include <stdlib.h>

/**
 * Implementation of a growing array.
 *
 * This is based on the implementation of Jorge Caponas project on his blog:
 * https://medium.com/@jcapona/dynamic-array-implementation-cpp-9deadaf1ba8e
 *
 * Github: https://github.com/jcapona/data_structures
 *
 * @author Uwe Rosner
 * @date 14/12/2018
 */
 
template <class T>
class Array {
  public:
    Array();
    ~Array();

    bool Push(T value);
    T Pop();
    void Set(size_t index, T value);
    const T Get(size_t index) const;

    size_t Size() const;
    size_t Capacity() const;
    int IsEmpty() const;

  private:
    size_t m_Capacity;
    size_t m_Size;
    T* m_pData;
    bool resize();
};

#endif
