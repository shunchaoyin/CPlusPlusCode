#include "Node.h"
#include <iostream>
#include <algorithm>
#include <queue>

Node::Node(int e)
{
    _value = e;
    std::cout << "construct node(" << _value << ")" << std::endl;
}

Node::Node()
{
    std::cout << "construct node(" << _value << ")" << std::endl;
}

Node::~Node()
{
    // clear(this);
    if (_rChild != nullptr)
    {
        delete _rChild;
    }
    if (_lChild != nullptr)
    {
        delete _lChild;
    }
    std::cout << "delete node(" << _value << ")" << std::endl;
    // delete this;
}
void Node::setLChild(Node *node)
{
    _lChild = node;
}
void Node::setRChild(Node *node)
{
    _rChild = node;
}

void Node::clear(Node *node)
{
    if (node->_rChild != nullptr)
    {
        clear(node->_rChild);
    }
    if (node->_lChild != nullptr)
    {
        clear(node->_lChild);
    }
    delete node;
    std::cout << "delete node(" << _value << ")" << std::endl;
}

bool Node::isLeafNode() const
{
    return _lChild == nullptr && _rChild == nullptr;
}

int Node::degree() const
{
    if (nullptr == _lChild && nullptr == _rChild)
    {
        return 0;
    }
    if (nullptr != _lChild && nullptr != _rChild)
    {
        return 2;
    }
    return 1;
}

int Node::depth(const Node *node) const
{
    int lCount = 0;
    int rCount = 0;
    if (nullptr != node->_lChild)
    {
        lCount = depth(node->_lChild);
    }
    if (nullptr != node->_rChild)
    {
        rCount = depth(node->_rChild);
    }

    return std::max(lCount, rCount) + 1;
}

int Node::depth() const
{
    int lCount = 0;
    int rCount = 0;
    if (nullptr == this)
    {
        return 0;
    }
    if (nullptr != _lChild)
    {
        lCount = _lChild->depth();
    }
    if (nullptr != _rChild)
    {
        rCount = _rChild->depth();
    }

    return std::max(lCount, rCount) + 1;
}

int Node::count(Node *node) const
{
    int nCount = 0;
    if (nullptr == node)
    {
        return 0;
    }
    if (node == nullptr)
    {
        return 0;
    }
    if (nullptr == node->_lChild && nullptr == node->_rChild)
    {
        return 1;
    }
    if (nullptr != node->_lChild && nullptr != node->_rChild)
    {
        return nCount += count(node->_lChild) + count(node->_rChild);
    }
    return nCount += std::max(count(node->_lChild), count(node->_rChild));
}

int Node::count() const
{
    int lCount = 0;
    int rCount = 0;
    if (nullptr == this)
    {
        return 0;
    }

    if (nullptr != _lChild)
    {
        lCount = _lChild->count();
    }
    if (nullptr != _rChild)
    {
        rCount = _rChild->count();
    }
    return lCount + rCount + 1;
}

int Node::getValue() const
{
    return _value;
}

void Node::preOrder(Visit visit)
{
    visit(this);
    if (nullptr != _lChild)
    {
        _lChild->preOrder(visit);
    }
    if (nullptr != _rChild)
    {
        _rChild->preOrder(visit);
    }
}

void Node::inOrder(Visit visit)
{
    if (nullptr != _rChild)
    {
        _rChild->inOrder(visit);
    }
    visit(this);
    if (nullptr != _lChild)
    {
        _lChild->inOrder(visit);
    }
}

void Node::postOrder(Visit visit)
{
    if (nullptr != _lChild)
    {
        _lChild->postOrder(visit);
    }
    if (nullptr != _rChild)
    {
        _rChild->postOrder(visit);
    }
    visit(this);
}

void Node::levelOrder(Visit visit)
{
    std::queue<Node *> q;
    q.push(this);
    while (!q.empty())
    {
        Node *node = q.front();
        q.pop();
        visit(node);
        if (nullptr != node->_lChild)
        {
            q.push(node->_lChild);
        }
        if (nullptr != node->_rChild)
        {
            q.push(node->_rChild);
        }
    }
}

void Node::invert()
{
    if (nullptr != _lChild)
    {
        _lChild->invert();
    }
    if (nullptr != _rChild)
    {
        _rChild->invert();
    }
    std::swap(_lChild, _rChild);
}