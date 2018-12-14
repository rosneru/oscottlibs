#ifndef OSCOTTLIBS_ARRAY_H_
#define OSCOTTLIBS_ARRAY_H_

#include <stdlib.h>

#define MIN_CAPACITY 10
#define GROWTH_FACTOR 2

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
    Array()
      : m_Capacity(MIN_CAPACITY),
        m_Size(0),
        m_pData((T*)malloc(m_Capacity * sizeof(*m_pData)))
    {
      if (m_pData == NULL)
      {
        m_Capacity = 0;
      }
    }


    ~Array()
    {
      free(m_pData);
    }


    bool Push(T value)
    {
      if (m_Size >= m_Capacity)
      {
        if(resize() == false)
        {
          return false;
        }
      }

      *(m_pData + m_Size++) = value;
      return true;
    }

    T Pop()
    {
      return *(m_pData + --m_Size);
    }

    void Set(size_t index, T value)
    {
      while (index >= m_Size)
      {
        this->Push(0);
      }

      *(m_pData + index) = value;
    }

    const T Get(size_t index) const
    {
      return *(m_pData + index);
    }

    size_t Size() const
    {
      return m_Size;
    }


    size_t Capacity() const
    {
      return m_Capacity;
    }

    bool IsEmpty() const
    {
      return m_Size == 0;
    }


  private:
    size_t m_Capacity;
    size_t m_Size;
    T* m_pData;

    bool resize()
    {
      if(m_Capacity == 0)
      {
        // If initial capacity could't be allocated the next allocation
        // would also fail
        return false;
      }

      size_t capacity = m_Capacity*GROWTH_FACTOR;
      T *tmp = (T*)realloc(m_pData, capacity * sizeof(*m_pData));
      if (!tmp)
      {
        return false;
      }

      m_pData = tmp;
      m_Capacity = capacity;
      return true;
    }

};

#endif
