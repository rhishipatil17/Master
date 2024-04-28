#ifndef STACK_H
#define STACK_H

#define STACK_MAX 1000

namespace DataStructure
{   
    class Stack
    {
        public:
            Stack();

            void push(int data);
            int pop();
            int peek();
            bool isEmpty();
            bool isFull();

        private:
            int stack[STACK_MAX];
            unsigned short int size;
            int *top;
    };
}

#endif