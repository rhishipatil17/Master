#include <iostream>
#include <memory>

class LL
{
    private:
        struct Node
        {
            int data;
            std::unique_ptr<Node> next;

            Node(const int& val, std::unique_ptr<Node> ptr) : data(val), next(std::move(ptr)) {}
        };

        std::unique_ptr<Node> hptr;

    public:
        LL() : hptr(nullptr) {}

        void print_ll() const
        {
            Node *temp = hptr.get();

            while(temp != nullptr)
            {
                std::cout << temp->data << " -> ";
                temp = temp->next.get();
            }
            std::cout << "nptr" << std::endl;
        }

        void insert_front(const int& data)
        {
            auto temp = std::make_unique<Node>(data, std::move(hptr));
            hptr = std::move(temp);
        }

        void reverse_ll()
        {
            std::unique_ptr<Node> prev{nullptr};
            std::unique_ptr<Node> cur{std::move(hptr)};
            std::unique_ptr<Node> next{nullptr};

            while(cur != nullptr)
            {
                next = std::move(cur->next);

                cur->next = std::move(prev);
                prev = std::move(cur);
                cur = std::move(next);
            }

            hptr = std::move(prev);
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
