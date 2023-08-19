#pragma once
#include <iostream>

namespace cantor
{
    class LinkedList
    {
    public:
        LinkedList() : front{new Node()}, back{new Node()}, count{0} {};

        ~LinkedList()
        {
            delete front;
            delete back;

            front = nullptr;
            back = nullptr;
            count = 0;
        }

        void push_back(int data)
        {
            if (!count)
            {
                list_init(data);

                return;
            }

            Node *node{new Node()};

            node->prev = back;
            node->data = data;
            back->next = node;

            back = node;

            ++count;
        }

        void push_front(int data)
        {
            if (!count)
            {
                list_init(data);

                return;
            }

            Node *node{new Node()};

            node->next = front;
            node->data = data;
            front->prev = node;

            front = node;

            ++count;
        }

        bool insert(int data, size_t index)
        {
            if (count < index)
                return false;

            Node *temp{front};

            for (int i{0}; i < index; ++i)
                temp = temp->next;

            Node *node{new Node()};
            node->data = data;
            node->next = temp;
            node->prev = temp->prev;

            (temp->prev)->next = node;
            temp->prev = node;

            ++count;
            return true;
        }

        int get(int index) const
        {
            Node node = *front;

            for (int i = 0; i < index; ++i)
                node = *(node.next);

            return node.data;
        }

        size_t size() const
        {
            return count;
        }

    private:
        struct Node
        {
            int data;
            Node *next;
            Node *prev;

            Node() : data{0}, next{nullptr}, prev{nullptr} {}
        };

        void list_init(int data)
        {
            front->data = data;
            back = front;

            ++count;
        }

        Node *front;
        Node *back;

        size_t count;
    };

    std::ostream &operator<<(std::ostream &os, const LinkedList &list)
    {
        os << '[';
        for (int i = 0; i < list.size(); i++)
        {
            os << list.get(i) << ", ";
        }
        os << ']' << '\n';

        return os;
    }
}