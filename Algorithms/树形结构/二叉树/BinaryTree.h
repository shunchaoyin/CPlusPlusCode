#pragma once
#include <iostream>
#include <map>
#include "Node.h"

class BinaryTree
{
private:
    Node *_root = nullptr;

    Node *create(std::map<int, int> &tree, int i);

public:
    BinaryTree(/* args */);
    BinaryTree(std::map<int, int> &tree);
    ~BinaryTree();
    int count() const;
    int depth() const;
    void preOrder(Node::Visit visit);
    void inOrder(Node::Visit visit);
    void postOrder(Node::Visit visit);
    void levelOrder(Node::Visit visit);
    void invert();
};
