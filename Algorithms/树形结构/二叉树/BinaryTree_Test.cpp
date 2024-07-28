#include <iostream>
#include <gtest/gtest.h>
#include "Node.h"
#include "BinaryTree.h"

TEST(Node, constructor)
{
    Node *node = new Node(1);
    EXPECT_EQ(1, node->getValue());
    delete node;
}

TEST(Node, isLeafNode)
{
    Node *node = new Node(1);
    EXPECT_TRUE(node->isLeafNode());
    delete node;
}

TEST(Node, degree)
{
    Node *node = new Node(1);
    EXPECT_EQ(0, node->degree());
    Node *lChild = new Node(2);
    node->setLChild(lChild);
    EXPECT_EQ(1, node->degree());
    Node *rChild = new Node(3);
    node->setRChild(rChild);
    EXPECT_EQ(2, node->degree());
    delete node;
}

TEST(Node, depth)
{
    Node *node = new Node(1);
    EXPECT_EQ(1, node->depth());
    Node *lChild = new Node(2);
    node->setLChild(lChild);
    EXPECT_EQ(2, node->depth());
    Node *rChild = new Node(3);
    node->setRChild(rChild);
    EXPECT_EQ(2, node->depth());
    Node *llChild = new Node(4);
    lChild->setLChild(llChild);
    EXPECT_EQ(3, node->depth());
    delete node;
}

TEST(Node, count)
{
    Node *node = new Node(1);
    EXPECT_EQ(1, node->count());
    Node *lChild = new Node(2);
    node->setLChild(lChild);
    EXPECT_EQ(2, node->count());
    Node *rChild = new Node(3);
    node->setRChild(rChild);
    EXPECT_EQ(3, node->count());
    Node *llChild = new Node(4);
    lChild->setLChild(llChild);
    EXPECT_EQ(4, node->count());
    delete node;
}

TEST(Node, preOrder)
{
    Node *node = new Node(1);
    Node *lChild = new Node(2);
    Node *rChild = new Node(3);
    node->setLChild(lChild);
    node->setRChild(rChild);
    Node *llChild = new Node(4);
    Node *lrChild = new Node(5);
    Node *rlChild = new Node(6);
    Node *rrChild = new Node(7);
    rChild->setLChild(rlChild);
    rChild->setRChild(rrChild);
    lChild->setRChild(lrChild);
    lChild->setLChild(llChild);

    node->preOrder([](Node *node)
                   { std::cout << node->getValue() << std::endl; });
    delete node;
}

TEST(Node, inOrder)
{
    Node *node = new Node(1);
    Node *lChild = new Node(2);
    Node *rChild = new Node(3);
    node->setLChild(lChild);
    node->setRChild(rChild);
    Node *llChild = new Node(4);
    Node *lrChild = new Node(5);
    Node *rlChild = new Node(6);
    Node *rrChild = new Node(7);
    rChild->setLChild(rlChild);
    rChild->setRChild(rrChild);
    lChild->setRChild(lrChild);
    lChild->setLChild(llChild);
    node->inOrder([](Node *node)
                  { std::cout << node->getValue() << std::endl; });
    delete node;
}

TEST(Node, postOrder)
{
    Node *node = new Node(1);
    Node *lChild = new Node(2);
    Node *rChild = new Node(3);
    node->setLChild(lChild);
    node->setRChild(rChild);
    Node *llChild = new Node(4);
    Node *lrChild = new Node(5);
    Node *rlChild = new Node(6);
    Node *rrChild = new Node(7);
    rChild->setLChild(rlChild);
    rChild->setRChild(rrChild);
    lChild->setRChild(lrChild);
    lChild->setLChild(llChild);
    node->postOrder([](Node *node)
                    { std::cout << node->getValue() << std::endl; });
    delete node;
}

TEST(Node, levelOrder)
{
    Node *node = new Node(1);
    Node *lChild = new Node(2);
    Node *rChild = new Node(3);
    Node *llChild = new Node(4);
    Node *lrChild = new Node(5);
    Node *rlChild = new Node(6);
    Node *rrChild = new Node(7);
    rChild->setLChild(rlChild);
    rChild->setRChild(rrChild);
    lChild->setRChild(lrChild);
    lChild->setLChild(llChild);
    node->setLChild(lChild);
    node->setRChild(rChild);
    node->levelOrder([](Node *node)
                     { std::cout << node->getValue() << std::endl; });
    delete node;
}

TEST(Node, invert)
{
    Node *node = new Node(1);
    Node *lChild = new Node(2);
    Node *rChild = new Node(3);
    Node *llChild = new Node(4);
    Node *lrChild = new Node(5);
    Node *rlChild = new Node(6);
    Node *rrChild = new Node(7);
    rChild->setLChild(rlChild);
    rChild->setRChild(rrChild);
    lChild->setRChild(lrChild);
    lChild->setLChild(llChild);
    node->setLChild(lChild);
    node->setRChild(rChild);
    node->invert();
    node->levelOrder([](Node *node)
                     { std::cout << node->getValue() << std::endl; });
    delete node;
}

TEST(BinaryTree, constructor)
{
    BinaryTree *tree = new BinaryTree();
    EXPECT_EQ(tree->count(), 0);
    EXPECT_EQ(tree->depth(), 0);
    delete tree;
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}