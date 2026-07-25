#include <iostream>

class LL
{
    private:
        struct Node
        {
            int data;
            Node* next;

            Node(const int& val, Node* ptr = nullptr) : data(val), next(ptr) {}
        };

        Node* hptr;

    public:
        LL()
        {
            hptr = nullptr;
        }

        void print_ll()
        {
            Node* temp = hptr;
            while(temp != nullptr)
            {
                if(temp->next == nullptr)
                {
                    std::cout << temp->data << std::endl;
                }
                else
                {
                    std::cout << temp->data << " - ";
                }
                temp = temp->next;
            }
        }

        void insert_front(int data)
        {
            hptr = new Node(data, hptr);
        }

        void reverse_ll()
        {
            Node* prev = nullptr;
            Node* cur = hptr;
            Node* next = nullptr;

            while(cur != nullptr)
            {
                next = cur->next;

                cur->next = prev;
                prev = cur;
                cur = next;
            }

            hptr = prev;
        }
};

int main()
{
    LL first;

    first.insert_front(1);
    first.insert_front(2);
    first.insert_front(3);
    first.insert_front(4);

    first.print_ll();

    first.reverse_ll();
    first.print_ll();
    return 0;
}
