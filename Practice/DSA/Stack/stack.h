#ifndef STACK_H
#define STACK_H

class Stack
{
	public:
		Stack();
		~Stack();

		void pop(void);
		void push(const int data);
		int size(void);
		bool empty(void);

	private:
		class Node
		{
			public:
				Node()
				{
					data = 0;
					previous_node = 0;
				}
				~Node()
				{
					data = 0;
					delete previous_node;
					previous_node = 0;
				}

			private:
				int data;
				Node *previous_node;
		};

		int stack_size;
		Node *top;
};

#endif
