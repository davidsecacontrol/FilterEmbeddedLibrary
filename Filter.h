/* ***************************************************
**     Filtering library
**     Author: David Secades
**     Easy to use API to create all kinds of filters
**
*******************************************************
Future Updates:
* Add variable filter size                        - DONE
* Remove dynamic allocation                       - DONE
* Add template for filtering variable type        - DONE
* Add embedded systems standard recommendations   - DONE
* Add othe standard recomendations
* Keep library std-free                           - DONE
* Add google tests
* Add pre-designed filtering options
*/

#ifndef FILTER_H
#define FILTER_H

#include "Filter_utils.h"

template <typename Type, unsigned int N>
class Filter
{

public:
  void setCoeffs(float const *const numerator, float const *const denominator);
  Type Update(const Type new_value);

private:
  Type input[N] = {};
  Type output[N] = {};

  float numerator[N] = {};
  float denominator[N] = {};
};

// Filter definitions
template <typename Type, unsigned int N>
void Filter<Type, N>::setCoeffs(float const *const numerator, float const *const denominator)
{

  CopyArray(this->numerator, numerator, N);
  CopyArray(this->denominator, denominator, N);
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

#endif