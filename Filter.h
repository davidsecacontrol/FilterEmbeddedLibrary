/**
 * @file Filter.h
 * @author David Secades - davidsecacontrol@gmail.com
 * @brief Statically - allocated library for FIR & IIR filters with customizable filter size & data type
 * @version 0.2
 * @date 2025-07-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include <cassert>

#include "Filter_utils.h"

/**
 * @brief Main filter class.
 *
 * @tparam Type Filter input data type
 * @tparam N Filter length
 *
 * @note Template is statically allocated. For run-time filter creating, use explicit template instantiation.
 */
template <typename Type, unsigned int N>
class Filter
{

public:

  /// @cond
  float numerator[N] = {};
  float denominator[N] = {};
  /// @endcond

  
  void SetCoefficients(float const *const numerator, float const *const denominator);

  void SetCoefficientsFromZTransform(float const *const numerator, float const *const denominator);

  Type Update(const Type new_value);

private:
  Type input[N] = {};  // x[n]
  Type output[N] = {}; // y[n]
};


// Class function definitions (required in same file by templates) ------------------------------------------------------------

/**
 * @brief Copies directly the provided arrays as coefifcients of the difference equation
 *
 * @note Notice that b[0] is ignored in the computation.
 * @param numerator Filter input coefficients \f$a[k]\quad :\quad  y[n] = \sum_{k=0}^{N}a[k]*x[n-k] + \dots\f$
 * @param denominator Filter output coefficients \f$b[k]\quad :\quad y[n] = \dots + \sum_{k=1}^{N}b[k]*y[n-k]\f$
 *
 *
 */
template <typename Type, unsigned int N>
void Filter<Type, N>::SetCoefficients(float const *const numerator, float const *const denominator)
{

  // Store the inputs
  CopyArray(this->numerator, numerator, N);
  CopyArray(this->denominator, denominator, N);
}

/**
 * @brief Computes the filter coefficients from a z transform representation \f$ \frac{\sum_{k=0}^{N}a[k]*z^k}{\sum_{k=0}^{N}b[k]*z^k} \f$
 *
 * @param numerator Z transform numerator \f$a[k]\f$
 * @param denominator Z transofrm denominator \f$b[k]\f$
 */
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

/**
 * @brief Evaluates the difference equation to obtain the next output.
 *
 * @param new_value New filter input
 * @return Type New filter output
 */
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
