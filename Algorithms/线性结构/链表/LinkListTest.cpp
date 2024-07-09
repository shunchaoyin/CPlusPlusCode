#include <stdio.h>
#include <gtest/gtest.h>
#include "LinkLists.h"

TEST(ListedLink, constructor)
{
    LinkedList linkList;
    EXPECT_EQ(linkList.size(), 0);
}

TEST(ListLink, isEmpty)
{
    LinkedList linkList;
    EXPECT_EQ(linkList.isEmpty(), true);
    linkList.insert(0, 1);
    EXPECT_EQ(linkList.isEmpty(), false);
}

TEST(ListLink, getLastNode)
{
    LinkedList linkList;
    EXPECT_EQ(linkList.isEmpty(), true);
    for (int i = 0; i < 5; i++)
    {
        linkList.insert(i, i);
    }
    EXPECT_EQ(linkList.lastNode()->value, 4);
}

TEST(ListLink, sort)
{
    LinkedList linkList;
    for (int i = 0; i < 5; i++)
    {
        linkList.insert(i, 4 - i);
    }
    linkList.sort();
    EXPECT_EQ(linkList.firstNode()->value, 0);
    EXPECT_EQ(linkList.lastNode()->value, 4);
}

TEST(ListLink,reverse)
{
    LinkedList linkList;
    for(int i=0;i<5;i++)
    {
        linkList.insert(i,i);
    }
    linkList.reverse();
    EXPECT_EQ(linkList.firstNode()->value,4);
    EXPECT_EQ(linkList.lastNode()->value,0);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}