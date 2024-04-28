#include "slist.h"
#include <climits>

using namespace DataStructure;

SingleLinkedList::SingleLinkedList()
{
    hptr = nullptr;
    length = 0;
}

unsigned int SingleLinkedList::getLength()
{
    return length;
}

void SingleLinkedList::addBegin(int p_data)
{
    hptr = new node(p_data,hptr);
    length+=1; 
}

void SingleLinkedList::addEnd(int p_data)
{
    node *ptr = hptr;
    while(ptr->next != nullptr)
    {
        ptr = ptr->next;
    }
    ptr->next = new node(p_data, nullptr);
    ptr = nullptr;
    length+=1;
}

void SingleLinkedList::removeBegin()
{
    node *ptr = hptr;
    hptr = hptr->next;
    ptr->data = 0;
    ptr->next = nullptr;
    delete ptr;
}

void SingleLinkedList::removeEnd()
{
    if(hptr == nullptr)
        return;

    if(hptr->next == nullptr)
    {
        hptr->data = 0;
        delete hptr;
        hptr = nullptr;
        return;
    }
    
    node *ptr = hptr;
    while(ptr->next->next != nullptr)
    {
        ptr = ptr->next;
    }
    ptr->next->data = 0;
    delete ptr->next;
    ptr->next = nullptr;
}

int SingleLinkedList::operator[](unsigned int pos)
{
    node *ptr = hptr;
    if(pos > length-1)
    {
        return INT_MIN;
    }
    unsigned int count = 0;
    while(count != pos)
    {
        ptr = ptr-> next;
        count++;
    }
    ptr = nullptr;
    return ptr->data;
}