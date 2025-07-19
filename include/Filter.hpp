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

#include "Filter_utils.hpp"

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
  void SetCoefficients(float const *const numerator, float const *const denominator, unsigned int size);

  void SetCoefficientsFromZTransform(float const *const numerator, float const *const denominator, unsigned int size);

  Type Update(const Type new_value);

  void SetState(Type const *const input_state, Type const *const output_state);

  void ClearState();

private:
  Type m_input[N] = {};  // x[n]
  Type m_output[N] = {}; // y[n]

  float m_numerator[N] = {};
  float m_denominator[N] = {};
};

// Class function definitions (required in same file by templates) ------------------------------------------------------------

/**
 * @brief Copies directly the provided arrays as coefifcients of the difference equation
 *
 * @note Notice that b[0] is ignored in the computation.
 * @param numerator Filter input coefficients \f$a[k]\quad :\quad  y[n] = \sum_{k=0}^{N}a[k]*x[n-k] + \dots\f$
 * @param denominator Filter output coefficients \f$b[k]\quad :\quad y[n] = \dots + \sum_{k=1}^{N}b[k]*y[n-k]\f$
 * @param size Number of elements to copy. The rest is init to 0
 *
 */
template <typename Type, unsigned int N>
void Filter<Type, N>::SetCoefficients(float const *const numerator, float const *const denominator, unsigned int size)
{
  assert(size <= N);

  // Num,den are < N, flush array.
  if (size != N)
  {
    Type zero_setting[N] = {0};
    CopyArray(m_numerator, zero_setting,N);
    CopyArray(m_denominator, zero_setting,N);
  }

  // Store the inputs
  CopyArray(m_numerator, numerator, size);
  CopyArray(m_denominator, denominator, size);
}

/**
 * @brief Computes the filter coefficients from a z transform representation \f$ \frac{\sum_{k=0}^{N}a[k]*z^k}{\sum_{k=0}^{N}b[k]*z^k} \f$
 *
 * @param numerator Z transform numerator \f$a[k]\f$
 * @param denominator Z transofrm denominator \f$b[k]\f$
 * @param size Number of coefficients
 */
template <typename Type, unsigned int N>
void Filter<Type, N>::SetCoefficientsFromZTransform(float const *const numerator, float const *const denominator, unsigned int size)
{
  // If b[0] = 0, the filter coefficients are incorrect.
  assert(denominator[0] != 0);

  SetCoefficients(numerator, denominator);

  // Solve for y(z) by

  // normalizing filter coefficients (required b[0] = 1)
  DivideArrayElements(m_numerator, N, m_denominator[0]);
  DivideArrayElements(m_denominator, N, m_denominator[0]);

  // and negating b[2...N]
  for (unsigned int i = 1; i < N; i++)
  {
    m_denominator[i] *= -1.0f;
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
  AdvanceArray(m_input, N);
  AdvanceArray(m_output, N);

  // Introduce filter input
  m_input[0] = new_value;

  // Compute filter response
  m_output[0] = DotProduct(m_numerator, m_input, N) + DotProduct(m_denominator, m_output, N);

  return m_output[0];
}

template <typename Type, unsigned int N>
void Filter<Type, N>::SetState(Type const *const input_state, Type const *const output_state)
{
  CopyArray(m_input, input_state);
  CopyArray(m_output, output_state);
}

template <typename Type, unsigned int N>
void Filter<Type, N>::ClearState()
{
  for (unsigned int i = 0; i < N; i++)
  {
    m_input[i] = 0;
    m_output[i] = 0;
  }
}