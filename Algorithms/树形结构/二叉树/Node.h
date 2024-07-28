#pragma once

class Node
{

private:
    int _value = 0;
    Node *_lChild = nullptr;
    Node *_rChild = nullptr;

public:
    // using Visit = std::function<void(Node*)>;
    typedef void Visit(Node *node);

    Node();
    Node(int e);
    ~Node();
    void setLChild(Node *node);
    void setRChild(Node *node);
    void clear(Node *node);
    bool isLeafNode() const;
    int degree() const;
    int depth() const;
    int depth(const Node *node) const;
    int count(Node *node) const;
    int count() const;
    int getValue() const;
    void preOrder(Visit visit);
    void inOrder(Visit visit);
    void postOrder(Visit visit);
    void levelOrder(Visit visit);
    void invert();
};
