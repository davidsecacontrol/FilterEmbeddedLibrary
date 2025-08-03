/**
 * @file Filter_testing.cpp
 * @author David Secades (davidsecacontrol@gmail.com)
 * @brief Testing compilation for the Filter.h library
 * @version 0.1
 * @date 2025-08-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#include <gtest/gtest.h>

#include "Filter.hpp"

/* Test suite 1: PublicAPITests Collects tests to ensure the API works as expected. If it breaks, we'll find out
**
** Last updated: 01/08/2025
*/

// Create a FilterTestHelper class that derives from FilterTest to get access to protected members
template<typename Type, unsigned int N>
class FilterTestHelper : public Filter<Type,N> {
    public:
    Type* GetNumerator(){
        return this->m_numerator;
    }
    Type* GetDenominator(){
        return this->m_denominator;
    }
    Type* GetInputState(){
        return this->m_input;
    }
    Type* GetOutputState(){
        return this->m_output;
    }
};

/**
 * @brief Ensures num,den, input, output vectors are initialized correctly for SetCoefficients()
 * 
 */
TEST(PublicAPITests,SetCoefficients_InitializationsAreCorrect) {
    constexpr unsigned int N = 5;
    FilterTestHelper<float,N> test_filter;

    // Assign numerator & denominator
    float num[N] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    float den[N] = {-1.0f, -2.0f, -3.0f, -4.0f, -5.0f};

    test_filter.SetCoefficients(num,den);

    // Check numerator & denominator
    float* num_copied = test_filter.GetNumerator();
    float* den_copied = test_filter.GetDenominator();

    for(unsigned int i = 0; i < N ; i++){
        ASSERT_FLOAT_EQ(num[i],num_copied[i]);
        ASSERT_FLOAT_EQ(den[i],den_copied[i]);
    }

    // Check inputs & outputs initialiation is correct
    float* input_copied = test_filter.GetInputState();
    float* output_copied = test_filter.GetOutputState();
    
    for(unsigned int i = 0; i < N ; i++){
        ASSERT_FLOAT_EQ(input_copied[i],0.0f);
        ASSERT_FLOAT_EQ(output_copied[i],0.0f);
    }
}

/**
 * @brief Tests that num,den, input, output arrays are initialized correctly for SetCoefficientsFromZTransform()
 * 
 */
TEST(PublicAPITests,SetCoefficientsFromZTransform_InitializationsAreCorrect) {
    // Test values are computed properly
    constexpr unsigned int N = 5;
    FilterTestHelper<float,N> test_filter;

    // Assign numerator & denominator
    float num[N] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    float den[N] = {-1.0f, -2.0f, -3.0f, -4.0f, -5.0f};

    test_filter.SetCoefficientsFromZTransform(num,den);
    // Check numerator & denominator
    float* num_copied = test_filter.GetNumerator();
    float* den_copied = test_filter.GetDenominator();

    for(unsigned int i = 0; i < N ; i++){
        ASSERT_FLOAT_EQ(num[i]/den[0],num_copied[i]); 
        ASSERT_FLOAT_EQ(-den[i]/den[0],den_copied[i]);
    }

    // Check inputs & outputs initialiation is correct
    float* input_copied = test_filter.GetInputState();
    float* output_copied = test_filter.GetOutputState();
    
    for(unsigned int i = 0; i < N ; i++){
        ASSERT_FLOAT_EQ(input_copied[i],0.0f);
        ASSERT_FLOAT_EQ(output_copied[i],0.0f);
    }
}

/**
 * @brief Tests SetCoefficientsFromZTransform() can handle the division error when den[0] == 0 instead of throwing
 * 
 */
TEST(PublicAPITests,SetCoefficientsFromZTransform_HandlesDivideByZero) {
    // Test values are computed properly
    constexpr unsigned int N = 5;
    FilterTestHelper<float,N> test_filter;

    // Assign numerator & denominator
    float num[N] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    float den[N] = {0.0f, -2.0f, -3.0f, -4.0f, -5.0f};

    EXPECT_NO_THROW(test_filter.SetCoefficientsFromZTransform(num,den));
    
}

/**
 * @brief Tests Update() with a butterworth filter with precision 0.002f
 * 
 */
TEST(PublicAPITests,Update_TestFilterOutput) {
    constexpr unsigned int N = 6;
    float numerator[N] = {0.0013f,0.0064f,0.0128f,0.0128f,0.0064f,0.0013f};
    float denominator[N] = {1.0000f,-2.9754f,3.8060f,-2.5453f,0.8811f,-0.1254f};

    FilterTestHelper<float,N> butter_filter; // 5th order 0.2 rad/s normalized cutoff
    butter_filter.SetCoefficientsFromZTransform(numerator,denominator);

    // Compute output data:
    constexpr unsigned int n_samples = 10;
    float input[n_samples] = {9.8196f,-5.2901f,-5.0688f,10.4616f,1.0000f,-8.5595f,6.6869f,6.4656f,-9.2015f,-0.0000f};
    float output[n_samples] = {0};

    for(unsigned int i = 0; i < n_samples; i++){
        output[i] = butter_filter.Update(input[i]);
    }
    //Compare with expected output:
    float output_expected[n_samples] = {0.0126f,0.0937f,0.3163f,0.6556f,0.9728f,1.1665f,1.2315f,1.1774f,1.0356f,0.8850f};
    for(unsigned int i = 0; i < n_samples; i++){
        ASSERT_NEAR(output[i],output_expected[i],0.003f);
    }
}

/**
 * @brief Tests SetState() copies properly
 * 
 */
TEST(PublicAPITests,InitialziationTest_SetState) {
    // Test values are computed properly
    constexpr unsigned int N = 5;
    FilterTestHelper<float,N> test_filter;

    // Assign numerator & denominator
    float input_state[N] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    float output_state[N] = {-1.0f, -2.0f, -3.0f, -4.0f, -5.0f};

    test_filter.SetState(input_state,output_state);

    // Check inputs & outputs copy is correct
    float* input_copied = test_filter.GetInputState();
    float* output_copied = test_filter.GetOutputState();
    
    for(unsigned int i = 0; i < N ; i++){
        ASSERT_FLOAT_EQ(input_state[i],input_copied[i]);
        ASSERT_FLOAT_EQ(output_state[i],output_copied[i]);
    }
}

/**
 * @brief Tests ClearState() resets properly to 0
 * 
 */
TEST(PublicAPITests,InitialziationTest_ClearState) {
    // Test values are computed properly
    constexpr unsigned int N = 5;
    FilterTestHelper<float,N> test_filter;

    // Assign numerator & denominator
    float input_state[N] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    float output_state[N] = {-1.0f, -2.0f, -3.0f, -4.0f, -5.0f};

    test_filter.SetState(input_state,output_state);
    test_filter.ClearState();
    // Check inputs & outputs copy is correct
    float* input_copied = test_filter.GetInputState();
    float* output_copied = test_filter.GetOutputState();
    
    for(unsigned int i = 0; i < N ; i++){
        ASSERT_FLOAT_EQ(0.0f,input_copied[i]);
        ASSERT_FLOAT_EQ(0.0f,output_copied[i]);
    }
}