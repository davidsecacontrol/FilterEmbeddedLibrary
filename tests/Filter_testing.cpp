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
 * @brief Tests SetCoefficientsFromZTransform() can handle the division error when den[0] == 0 - TO BE IMPLEMENTED
 * 
 */
TEST(PublicAPITests,SetCoefficientsFromZTransform_HandlesDivideByZero) {
    // TBD
}

/**
 * @brief Tests Update() with a ____ filter - TO BE IMPLEMENTED
 * 
 */
TEST(PublicAPITests,ResultTest_Update) {
    // Ensure return value works as an expected filter: 
    //fx select a couple filters from MATLAB and test results match
    EXPECT_EQ(7*6,42);
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