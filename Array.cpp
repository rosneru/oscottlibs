#include <Array.h>
#include "SimpleString.h"

#define MIN_CAPACITY 10
#define GROWTH_FACTOR 2


template <class T>
Array<T>::Array()
  : m_Capacity(MIN_CAPACITY),
    m_Size(0),
    m_pData((T*)malloc(m_Capacity * sizeof(*m_pData)))
{
  if (m_pData == NULL)
  {
    m_Capacity = 0;
  }
}

template <class T>
Array<T>::~Array()
{
  free(m_pData);
}

template <class T>
bool Array<T>::Push(T value) {
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

template <class T>
T Array<T>::Pop()
{
  return *(m_pData + --m_Size);
}

template <class T>
void Array<T>::Set(size_t index, T value)
{
  while (index >= m_Size)
  {
    this->Push(0);
  }

  *(m_pData + index) = value;
}


template <class T>
T const Array<T>::Get(size_t index) const
{
  return *(m_pData + index);
}

template <class T>
size_t Array<T>::Size() const
{
  return m_Size;
}

template <class T>
size_t Array<T>::Capacity() const
{
  return m_Capacity;
}

template <class T>
bool Array<T>::resize()
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

template <class T>
int Array<T>::IsEmpty() const
{
  return m_Size == 0;
}

template class Array<int>;
template class Array<float>;
