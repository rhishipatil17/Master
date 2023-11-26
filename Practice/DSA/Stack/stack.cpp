#include<iostream>
#include"stack.h"

using namespace std;

Stack::Stack()
{
	top = 0;
	stack_size = 0;
}
Stack::~Stack()
{
	for(int i=0; i<stack_size; i++)
	{
		pop();
	}
	delete top;
	top = 0;
	stack_size = 0;
}

int Stack::pop(void)
{
	if(stack_size == 0)
	{
		return ~0;
	}

	Node *tmp = top;
	int data = tmp->data;
	top = top->previous_node;
	stack_size -= 1;

	delete tmp;
	return data;
}
void Stack::push(const int data)
{
	Node *tmp = new Node;
	tmp->data = data;
	tmp->previous_node = top;
	top = tmp;
	stack_size += 1;
}
int Stack::size(void)
{
	return stack_size;
}

bool Stack::empty(void)
{
	return stack_size ? true : false;
}
