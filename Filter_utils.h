#pragma once

#include <cassert>

template <typename Type>
Type DotProduct(Type const *const vec1, Type const *const vec2, const unsigned int size)
{

  Type result = 0;
  // Sum of the multiplication of each element
  for (unsigned int i = 0; i < size; i++)
  {
    result += vec1[i] * vec2[i];
  }
  return result;
}

template <typename Type>
void AdvanceArray(Type *const array, const unsigned int size)
{

  // Advance each value to the next index
  for (unsigned int i = size - 1; i > 0; i--)
  {
    array[i] = array[i - 1];
  }
  array[0] = 0;
}

template <typename Type>
void CopyArray(Type *const destination, Type const *const source, unsigned int size)
{
  for (unsigned int i = 0; i < size; i++)
  {
    destination[i] = source[i];
  }
}

template <typename Type>
void DivideArrayElements(Type *const array, unsigned int size, Type divisor)
{
  assert(divisor != 0);

  for (unsigned int i = 0; i < size; i++)
  {
    array[i] /= divisor;
  }
}
