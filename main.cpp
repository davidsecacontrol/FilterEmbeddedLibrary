#include <iostream>
#include "Filter.h"

constexpr unsigned int filter_size = 5;
Filter<float,filter_size> moving_average;
int main(){
    float num[] = {0.2,0.2,0.2,0.2,0.2};
    float den[] = {1,0,0,0,0};
    moving_average.Initialize(num,den);
    std::cout << "Hello world" << std::endl;

    while(true){
        float new_sample;
        std::cin >> new_sample;
        
        std::cout << moving_average.Update(new_sample) << std::endl;
    }
    return 0;
}
