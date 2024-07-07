#include <iostream>
#include <stdlib.h>
#include "LinkLists.h"

LinkedList::LinkedList()
{
    _head = NULL;
}
LinkedList::~LinkedList()
{
    while (_head != NULL)
    {
        Node *tmp = _head;
        _head = tmp->next;
        delete tmp;
    }
}
int LinkedList::size() const
{
    int count = 0;
    Node *tmp = _head;
    while (tmp != NULL)
    {
        count++;
        tmp = tmp->next;
    }
    return count;
}
bool LinkedList::isEmpty() const
{
    return _head == NULL;
}
Node *LinkedList::lastNode() const
{
    if (NULL == _head)
    {
        return NULL;
    }
    Node *tmp = _head;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    return tmp;
}
Node *LinkedList::firstNode() const
{
    return _head;
}
Node *LinkedList::getNode(int pos) const
{
    if (pos > size() && pos < 0)
    {
        return NULL;
    }
    int count = 0;
    Node *tmp = _head;
    while (count < pos)
    {
        tmp = tmp->next;
        count++;
    }
    return tmp;
}

Node *LinkedList::findNode(int e) const
{
    if (isEmpty())
    {
        return NULL;
    }
    Node *tmp = _head;
    while (tmp->value != e)
    {
        tmp = tmp->next;
    }
    return tmp;
}

int LinkedList::getValue(int pos) const
{
    Node *tmp = getNode(pos);
    if (NULL == tmp)
    {
        return ERROR_REPORT;
    }
    return tmp->value;
}
void LinkedList::setValue(int pos, int e)
{
    Node *tmp = getNode(pos);
    if (NULL != tmp)
    {
        tmp->value = e;
    }
}
int LinkedList::insert(int pos, int e)
{
    if (pos < 0)
    {
        return ERROR_REPORT;
    }
    Node *newNode = new Node();
    newNode->value = e;
    if (pos == 0)
    {
        newNode->next = _head;
        _head = newNode;
        return 0;
    }

    Node *lastNode = getNode(pos - 1);
    if (NULL == lastNode)
    {
        return ERROR_REPORT;
    }
    Node *nextNode = lastNode->next;

    lastNode->next = newNode;
    newNode->next = nextNode;
    return 0;
}
int LinkedList::remove(int pos)
{
    if (pos < 0)
    {
        return ERROR_REPORT;
    }
    if (pos == 0)
    {
        Node *tmp = _head;
        _head = _head->next;
        delete tmp;
        return 0;
    }
    Node *lastNode = getNode(pos - 1);

    if (NULL == lastNode)
    {
        return ERROR_REPORT;
    }
    Node *tmp = lastNode->next;
    lastNode->next = tmp->next;
    delete tmp;
}

void LinkedList::reverse()
{
    if (_head == NULL && _head->next == NULL)
    {
        return;
    }
    Node *tmp = _head;
    LinkedList *newLink = NULL;
    while (tmp->next != NULL)
    {
        newLink->insert(0, tmp->value);
        tmp = tmp->next;
    }
    _head = newLink->_head;
}
void LinkedList::sort()
{
    Node *setValue = _head;
    Node *p = setValue->next;
    while (NULL != setValue->next)
    {
        p = setValue->next;
        while (NULL != p)
        {
            if (setValue->value > p->value)
            {
                int tmp = setValue->value;
                setValue->value = p->value;
                p->value = tmp;
            }
            p= p->next;
        }
        setValue = setValue->next;
    }
}