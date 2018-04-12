#include <gtest/gtest.h> 

TEST(Dummy, isOneReallyOne) {
    ASSERT_EQ(1,1.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
