# FilterEmbeddedLibrary
This repository contains a statically allocated, STL-free digital signal processing library for embedded systems.

## Installation
Copy all files from [include](include) into your headers folder.
## Usage
Instantiate the 'Filter' class and provide the filter weights:

```c++
  #include "Filter.h"
  Filter<OUTPUT_TYPE,FITLER_SIZE> my_filter;
  my_filter.(input_coeffs,output_coeffs);
```

Now, every new measurement can be filtered (See examples 1,2):
``` c++
  float new_filtered_value = my_filter.Update(new_value);
```

The Z transform coefficients can also be supplied and the library will automatically convert them to the filter weights:
``` c++
  my_filter.SetCoefficientsFromZTransform(numerator,denominator);
```

Although not recommended, it is possible to change the filter states to avoid transients:
``` c++
  my_filter.SetState(input_state,output_state);
```

## Compilation
This repository uses CMake. It is already configured for CMake Tools extension and runs on the default generator.

## Documentation
This reopsitory uses doxygen. For Windows, run `doxygen Doxyfile`.

## Future Updates
This repository is also a learning experience. The expected roadmap is:
- [X] Add variable filter size
- [X] Remove dynamic allocation
- [X] Add template for filtering variable type
- [X] Add embedded systems standard recommendations
- [ ] Add other standard recomendations (AUTOSAR/ C++ standards)
- [X] Keep library std-free
- [X] Add CMake compilation
- [ ] Add google tests                                          
- [ ] Add pre-designed filtering options
- [X] Add doxygen docuemntation

