#define ERROR_REPORT 0XEFEFEFEF

class Node
{
public:
    int value;
    Node *next;
};
class LinkedList
{
private:
    Node *_head;

public:
    LinkedList();
    ~LinkedList();
    int size() const;
    bool isEmpty() const;
    Node *lastNode() const;
    Node *firstNode() const;
    Node *getNode(int pos) const;
    Node *findNode(int e) const;
    int getValue(int pos) const;
    void setValue(int pos, int e);
    int insert(int pos, int e);
    int remove(int pos);
    void reverse();
    void sort();
};