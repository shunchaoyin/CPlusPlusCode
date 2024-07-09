#include <stdio.h>
#include <gtest/gtest.h>
#include "Stack.h"

TEST(Stack, constructor)
{
    Stack stack;
    EXPECT_EQ(stack.size(), 0);
}

TEST(Stack, isempty)
{
    Stack stack;
    EXPECT_EQ(stack.isEmpty(), true);
    stack.push(0);
    EXPECT_EQ(stack.isEmpty(), false);
}

TEST(Stack, isfull)
{
    Stack stack;
    EXPECT_EQ(stack.isFull(), false);
    stack.push(0);
    stack.push(1);
    stack.push(2);
    EXPECT_EQ(stack.isFull(), true);
}

TEST(Stack, getSize)
{
    Stack stack;
    EXPECT_EQ(stack.size(), 0);
    stack.push(0);
    EXPECT_EQ(stack.size(), 1);
    stack.push(1);
    EXPECT_EQ(stack.size(), 2);
    stack.push(2);
    EXPECT_EQ(stack.size(), 3);
    EXPECT_EQ(stack.isFull(), true);
}

TEST(Stack, getTop)
{
    Stack stack;
    EXPECT_EQ(stack.top(), ERROR_RET);
    stack.push(0);
    EXPECT_EQ(stack.top(), 0);
    stack.push(1);
    EXPECT_EQ(stack.top(), 1);
    stack.push(2);
    EXPECT_EQ(stack.top(), 2);
}

TEST(Stack, push)
{
    Stack stack;
    EXPECT_EQ(stack.top(), ERROR_RET);
    stack.push(0);
    EXPECT_EQ(stack.top(), 0);
    stack.push(1);
    EXPECT_EQ(stack.top(), 1);
    stack.push(2);
    EXPECT_EQ(stack.top(), 2);
}

TEST(Stack, pop)
{
    Stack stack;
    stack.push(0);
    stack.push(1);
    stack.push(2);
    EXPECT_EQ(stack.top(), 2);
    stack.pop();
    EXPECT_EQ(stack.top(), 1);
    stack.pop();
    EXPECT_EQ(stack.top(), 0);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
