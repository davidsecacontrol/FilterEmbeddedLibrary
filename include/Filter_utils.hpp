/**
 * @file Filter_utils.h
 * @author David Secades (davidsecacontrol@gmail.com)
 * @brief Compialtion of useful, statically allocated, STL-free functions.
 * @version 0.1
 * @date 2025-07-11
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once



/**
 * @brief Computes the dot product of two vectors of length \p size
 *
 * @tparam Must implement operator+=(Type), operator*(Type), =0 initialization.
 * @param vec1 First array to multiply
 * @param vec2 Second array to multiply
 * @param size Array size
 * @return Type Result of dot product
 */
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

/**
 * @brief Moves the elements in \p array from index k to k+1 up until \p size. \p array [0] initialized to zero
 *
 * @tparam Type Must implement operator=(Type) and =0 initialization
 * @param array Array to advance
 * @param size  Size of \p array
 */
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

/**
 * @brief Makes a copy of the first \p size elements of \p source at \p destination. User must ensure memory safety
 *
 * @tparam Type Must implement operator=(Type)
 * @param destination Array to copy into
 * @param source Array to be copied
 * @param size Number of indexes to copy.
 */

template <typename Type>
void CopyArray(Type *const destination, Type const *const source, unsigned int size)
{
  
  for (unsigned int i = 0; i < size; i++)
  {
    destination[i] = source[i];
  }
}

/**
 * @brief Divides all elements of \p array up to index \p size by \p divisor
 *
 * @tparam Type Must implement operator!=(int), operator/=(Type)
 * @param array Array to be divided
 * @param size Size of \p array
 * @param divisor Value to divide by
 */
template <typename Type>
void DivideArrayElements(Type *const array, unsigned int size, Type divisor)
{
  
  for (unsigned int i = 0; i < size; i++)
  {
    array[i] /= divisor;
  }
}
