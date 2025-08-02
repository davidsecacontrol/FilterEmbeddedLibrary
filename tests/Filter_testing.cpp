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

TEST(PublicAPITests,InitializationTest_SetCoefficients) {
    // test values are copied properly
    // Test states are set properly(0...0,0...0)
    EXPECT_EQ(7*6,42);
}


TEST(PublicAPITests,InitializationTest_SetCoefficientsFromZTransform) {
    // Test values are computed proeprly
    // Test states are set properly (0...0,0...0)
    EXPECT_EQ(7*6,42);
}

TEST(PublicAPITests,ResultTest_Update) {
    // Ensure return value works as an expected filter: 
    //fx select a couple filters from MATLAB and test results match
    EXPECT_EQ(7*6,42);
}

TEST(PublicAPITests,InitialziationTest_SetState) {
    // Test values are computed properly
    // Test states are set properly (0...0,0...0)
    EXPECT_EQ(7*6,42);
}