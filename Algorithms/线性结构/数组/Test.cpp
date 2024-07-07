#include "gtest/gtest.h"
#include "Array.h"

TEST(Array, Constructor)
{
    Array a(10, 5, 0);
    EXPECT_EQ(a.size(), 5);
    EXPECT_EQ(a.capacity(), 10);
    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(a[i], 0);
    }
}
TEST(Array, CopyConstructor)
{
    Array a(10, 5, 0);
    Array b(a);
    EXPECT_EQ(b.size(), 5);
    EXPECT_EQ(b.capacity(), 10);
    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(b[i], 0);
    }
}
TEST(Array, Insert)
{
    Array a(10, 5, 0);
    a.insert(2, 1);
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.capacity(), 10);
    for (int i = 0; i < 2; i++)
    {
        EXPECT_EQ(a[i], 0);
    }
    EXPECT_EQ(a[2], 1);
    for (int i = 3; i < 6; i++)
    {
        EXPECT_EQ(a[i], 0);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}