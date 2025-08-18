# FilterEmbeddedLibrary
This repository contains a statically allocated, STL-free digital signal processing library for embedded systems.

## Installation
Copy all files from [include](include) into your headers folder.
## Usage
Instantiate the 'Filter' class and provide the filter weights:

```c++
  #include "Filter.h"
  Filter<OUTPUT_TYPE,FITLER_SIZE> my_filter;
  my_filter.SetCoefficients(input_coeffs,output_coeffs);
```

Now, every new measurement can be filtered (See examples 1,2):
``` c++
  OUTPUT_TYPE new_filtered_value = my_filter.Update(new_value);
```

Besides, the Z transform numerator & denominator coefficients (from f.x. MATLAB) can be supplied instead and the library will automatically convert them to the filter weights:
``` c++
  my_filter.SetCoefficientsFromZTransform(numerator,denominator);
```
The filter can be cleared for easy reinitialziation:
``` c++
  my_filter.ClearState();
```

Finally although not recommended, it is possible to change the filter states:
``` c++
  my_filter.SetState(input_state,output_state);
```


## Compilation
For usage of this library, check [installation](#Installation) chapter.

For development, this repository uses CMake. It is already configured for the [CMake Tools extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) and runs on the default generator.

## Documentation
This repository uses doxygen. For Windows, run `doxygen Doxyfile`.

## Future Updates
The expected roadmap is:
- [X] Add variable filter size
- [X] Remove dynamic allocation
- [X] Add template for filtering variable type
- [X] Add embedded systems standard recommendations
- [ ] Add other standard recomendations (AUTOSAR/ C++ standards)
- [X] Keep library std-free
- [X] Add CMake compilation
- [X] Add google tests                                          
- [ ] Add pre-designed filtering options
- [X] Add doxygen docuemntation

