#include "BinaryTree.h"
BinaryTree::BinaryTree(/* args */)
{
    
}

BinaryTree::BinaryTree(std::map<int,int> &tree)
{
    _root = create(tree, 1);
}
BinaryTree::~BinaryTree()
{
    if (_root != nullptr)
    {
        delete _root;
    }
}

Node* BinaryTree::create(std::map<int,int> &tree, int i)
{
    if (tree.find(i) == tree.end())
    {
        return nullptr;
    }
    Node *node = new Node(i);
    node->setLChild(create(tree, 2*i));
    node->setRChild(create(tree, 2*i+1));
    return node;
}

int BinaryTree::count() const
{
    return _root->count();
}

int BinaryTree::depth() const
{
    return _root->depth();
}

void BinaryTree::preOrder(Node::Visit visit)
{
    _root->preOrder(visit);
}

void BinaryTree::inOrder(Node::Visit visit)
{
    _root->inOrder(visit);
}

void BinaryTree::postOrder(Node::Visit visit)
{
    _root->postOrder(visit);
}

void BinaryTree::levelOrder(Node::Visit visit)
{
    _root->levelOrder(visit);
}

void BinaryTree::invert()
{
    _root->invert();
}

