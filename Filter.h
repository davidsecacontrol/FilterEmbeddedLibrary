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
**                  + b[1]*y[n-1] + b[2]*y[n-2] + ... + b[N-1]*y[n-1-(N-1)]
**
**      or: 
**
**          y(z)       a[0] + a[1]*z + ... + a[N-1]*z^(N-1)
**        --------- = ------------------------------------------
**          x(z)       b[0] + b[1]*s + ... + b[N-1]*z[N-1]
**
**     Where:
**        numerator[n] <-> a[n]
**        denominator[n] <-> b[n]
** 
**           
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


#include <cassert>

#include "Filter_utils.h"


template <typename Type, unsigned int N>
class Filter
{

public:
  float numerator[N] = {};    // a[]        where a[0] <-> x[n]
  float denominator[N] = {};  // b[]      where b[0] = 1 <-> y[n]

  // Normalizes b[n] such that b[0] = 1
  void setCoeffs(float const *const numerator, float const *const denominator);

  // Compute next filter respose
  Type Update(const Type new_value);

private:
  Type input[N] = {};         // x[n]
  Type output[N] = {};        // y[n]

  
  
};

// Filter definitions ----------------------------------------------------------------------

template <typename Type, unsigned int N>
void Filter<Type, N>::setCoeffs(float const *const numerator, float const *const denominator)
{
  // If b[0] = 0, the filter coefffs are incorrect.
  assert(denominator[0] != 0);

  // Store the inputs
  CopyArray(this->numerator, numerator, N);
  CopyArray(this->denominator, denominator, N);

  // Solve for y(z) by normalizing filter coefficients (required b[0] = 1)
  DivideArrayElements(this->denominator,N, this->denominator[0]);



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