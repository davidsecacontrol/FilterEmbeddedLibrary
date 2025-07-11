/**
 * @file main.cpp
 * @author David Secades (davidsecacontrol@gmail.com)
 * @brief Example 1: Moving average filter with user input
 * @version 0.1
 * @date 2025-07-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <iostream>
#include "Filter.h"

/**
 * @brief Example 1: Moving average with user input
 *
 * @return int
 */
int main()
{
    float num[] = {0.2, 0.2, 0.2, 0.2, 0.2};
    float den[] = {1, 0, 0, 0, 0};

    constexpr unsigned int FILTER_SIZE = 5;
    Filter<float, FILTER_SIZE> moving_average;
    moving_average.SetCoefficients(num, den);

    std::cout << "Selected filter is moving average(5)" << std::endl;

    int i = 0;
    while (true)
    {
        float new_sample;
        std::cout << "Input " << i << ":";
        std::cin >> new_sample;

        std::cout << "Output " << i << ":" << moving_average.Update(new_sample) << std::endl;
        ++i;
    }
    return 0;
}
