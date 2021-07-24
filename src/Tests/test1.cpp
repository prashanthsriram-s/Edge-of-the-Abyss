#include <gtest/gtest.h>
#include "playerSimulator.cpp"

TEST(INITTEST, INITTEST1) {
    
    EXPECT_EQ(0, 0);
}
 
/*TEST(SquareRootTest, NegativeNos) {
    ASSERT_EQ(-1.0, squareRoot(-15.0));
    ASSERT_EQ(-1.0, squareRoot(-0.2));
}*/
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
