#include <gtest/gtest.h>
#include "cpp_project/calculator.h"

class CalculatorTest : public ::testing::Test {
protected:
    Calculator calc;
};

TEST_F(CalculatorTest, TestAdd) {
    EXPECT_DOUBLE_EQ(calc.add(5.0, 3.0), 8.0);
    EXPECT_DOUBLE_EQ(calc.add(-5.0, 3.0), -2.0);
    EXPECT_DOUBLE_EQ(calc.add(0.0, 0.0), 0.0);
}

TEST_F(CalculatorTest, TestSubtract) {
    EXPECT_DOUBLE_EQ(calc.subtract(5.0, 3.0), 2.0);
    EXPECT_DOUBLE_EQ(calc.subtract(-5.0, 3.0), -8.0);
    EXPECT_DOUBLE_EQ(calc.subtract(10.0, 10.0), 0.0);
}

TEST_F(CalculatorTest, TestMultiply) {
    EXPECT_DOUBLE_EQ(calc.multiply(5.0, 3.0), 15.0);
    EXPECT_DOUBLE_EQ(calc.multiply(-5.0, 3.0), -15.0);
    EXPECT_DOUBLE_EQ(calc.multiply(0.0, 100.0), 0.0);
}

TEST_F(CalculatorTest, TestDivide) {
    EXPECT_DOUBLE_EQ(calc.divide(10.0, 2.0), 5.0);
    EXPECT_DOUBLE_EQ(calc.divide(-10.0, 2.0), -5.0);
    EXPECT_THROW(calc.divide(10.0, 0.0), std::runtime_error);
}
