/* ***************************************************
**     Filtering library
**     Author: David Secades
**     Easy to use API to create all kinds of filters
**
**   - Statically allocated
**   - STL - independent
**   - Customizable data type & filter size
**
** -------------------------------------------------------------
**
**     Implements digital filters of the type:
**
**       y[n] =  a[0]*x[n] + a[1]*x[n-1] + ... + a[N-1]*x[n-(N-1)]
**                  + b[1]*y[n-1] + b[2]*y[n-2] + ... + b[N-1]*y[n-(N-1)]
**
**      with SetCoefficients(a,b) 
**
**      or:
**
**          y(z)       a[0] + a[1]*z + ... + a[N-1]*z^(N-1)
**        --------- = ------------------------------------------
**          x(z)       b[0] + b[1]*z + ... + b[N-1]*z^(N-1)
**
**     with SetCoefficientsFromZTransform(a,b)
**
**
**
**     Where:
**        numerator[n] <-> a[n]
**        denominator[n] <-> b[n]
**
**
**
*******************************************************
*/

#pragma once

#include <cassert>

#include "Filter_utils.h"

template <typename Type, unsigned int N>
class Filter
{

public:
  float numerator[N] = {};   // a[]        where a[0] <-> x[n]
  float denominator[N] = {}; // b[]      where b[0] = 1 <-> y[n]

  void SetCoefficients(float const *const numerator, float const *const denominator);
  // Computes filter coefficients from z transform
  void SetCoefficientsFromZTransform(float const *const numerator, float const *const denominator);

  // Compute next filter respose
  Type Update(const Type new_value);

private:
  Type input[N] = {};  // x[n]
  Type output[N] = {}; // y[n]
};

// Filter definitions ----------------------------------------------------------------------

template <typename Type, unsigned int N>
void Filter<Type, N>::SetCoefficients(float const *const numerator, float const *const denominator)
{

  // Store the inputs
  CopyArray(this->numerator, numerator, N);
  CopyArray(this->denominator, denominator, N);
}

template <typename Type, unsigned int N>
void Filter<Type, N>::SetCoefficientsFromZTransform(float const *const numerator, float const *const denominator)
{
  SetCoefficients(numerator, denominator);

  // If b[0] = 0, the filter coefficients are incorrect.
  assert(denominator[0] != 0);

  // Solve for y(z) by

  // normalizing filter coefficients (required b[0] = 1)
  DivideArrayElements(this->numerator, N, this->denominator[0]);
  DivideArrayElements(this->denominator, N, this->denominator[0]);

  // and negating b[2...N]
  for (unsigned int i = 1; i < N; i++)
  {
    this->denominator[i] *= -1.0f;
  }
}

template <typename Type, unsigned int N>
Type Filter<Type, N>::Update(const Type new_value)
{
  // Next time instant
  AdvanceArray(input, N);
  AdvanceArray(output, N);

  // Introduce filter input
  input[0] = new_value;

  // Compute filter response
  output[0] = DotProduct(numerator, input, N) + DotProduct(denominator, output, N);

  return output[0];
}
