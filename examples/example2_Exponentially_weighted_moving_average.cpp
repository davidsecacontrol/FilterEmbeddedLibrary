
/**
 * @file example2_Exponentially_weighted_moving_average.cpp
 * @author David Secades (davidsecacontrol@gmail.com)
 * @brief Implementation of a exponentially weighted moving average filter
 * @version 0.1
 * @date 2025-07-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <iostream>
#include <random>
#include <array>
#include <algorithm>
#include <numeric>
#include <cmath>

#include "Filter.hpp"

/// @cond
constexpr double PI = 3.14159265358979323846;


float SineWaveWithNoiseSample(const float time,const float frequency, const float gain, const float noise_std_dev );


int main()
{
    std::cout << "Selected filter is exponentially weighted moving average" << std::endl;


    // Generate a sin wave with normal noise
    constexpr unsigned int number_of_samples = 40;
    std::array<float,number_of_samples> timeData;
    std::array<float,number_of_samples> inputData;
    {
        constexpr float frequency = 10; // Hz
        constexpr float gain = 10;
        constexpr float noise_std_dev = 1.5;

        
        std::iota(timeData.begin(),timeData.end(),1); // Fill time with 1,2,3,...
        std::transform(timeData.begin(),timeData.end(),inputData.begin(),[&](float time){   // Compute input
            return SineWaveWithNoiseSample(time,frequency,gain,noise_std_dev);
        });
    }

    // Create the filter
    constexpr unsigned int FILTER_SIZE = 2;
    constexpr float lambda = 0.5;

    float num[] = {lambda,0};
    float den[] = {1,1-lambda};

    Filter<float, FILTER_SIZE> EWMA_filter;
    EWMA_filter.SetCoefficients(num, den);

    // Apply the filter to all the data
    std::array<float,number_of_samples> outputData;

    std::transform(inputData.begin(),inputData.end(),outputData.begin(),[&](float sample){   
       return EWMA_filter.Update(sample);
    });


    // Printing
    std::cout << "Input data:\n[";
    std::for_each(inputData.begin(),inputData.end(), [&](float sample){
        std::cout << sample << ",";
    });
    std::cout << "\b]\n";

    std::cout << "Output data:\n[";
    std::for_each(outputData.begin(),outputData.end(), [&](float sample){
        std::cout << sample << ",";
    });
    std::cout << "\b]\n";

    return 0;
}


float SineWaveWithNoiseSample(const float time,const float frequency, const float gain, const float noise_std_dev ){
    static std::default_random_engine generator;
    static std::normal_distribution<float> distribution(0,noise_std_dev); // mean,sdev
    return std::sin(2*PI*time/frequency)*gain + distribution(generator);
}
/// @endcond
