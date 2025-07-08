/* ***************************************************
**     Filtering library
**     Author: David Secades
**     Easy to use API to create all kinds of filters
**
*******************************************************
Updates:
* Add variable filter size                        - DONE
* Remove dynamic allocation                       - DONE
* Add template for filtering variable type        - DONE
* Add embedded systems standard recommendations
* Add othe standard recomendations
* Keep library std-free                           - DONE
* Add google tests
*/

#ifndef FILTER_H
#define FILTER_H

#include "Filter_utils.h"

template <typename Type, unsigned int N>
class Filter
{

public:
  void setCoeffs(Type const *const num, Type const *const den);
  Type Update(const Type new_value);

private:
  Type input[N] = {0};
  Type output[N] = {0};

  Type numerator[N] = {0};
  Type denominator[N] = {0};
};

// Filter definitions
template <typename Type, unsigned int N>
void Filter<Type, N>::setCoeffs(Type const *const num, Type const *const den)
{
  for (unsigned int i = 0; i < N; i++)
  {
    numerator[i] = num[i];
    denominator[i] = den[i];
  }
}

template <typename Type, unsigned int N>
Type Filter<Type, N>::Update(const Type new_value)
{
  Advance_Array<Type>(input, N);
  Advance_Array<Type>(output, N);

  input[0] = new_value;
  output[0] = Dot_Product<Type>(numerator, input, N) + Dot_Product<Type>(denominator, output, N);

  return output[0];
}

#endif