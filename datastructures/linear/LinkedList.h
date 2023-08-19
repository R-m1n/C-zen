#pragma once
#include <iostream>

namespace cantor
{
    class LinkedList
    {
    public:
        enum class Error : int
        {
            Success,
            Failure
        };

        LinkedList() : front{new Node()}, back{new Node()}, count{0} {};

        ~LinkedList()
        {
            delete front;
            delete back;

            front = nullptr;
            back = nullptr;
            count = 0;
        }

        Error push_back(int data)
        {
            if (!count)
            {
                list_init(data);

                return Error::Success;
            }

            Node *node{new Node()};

            node->prev = back;
            node->data = data;
            back->next = node;

            back = node;

            ++count;
            return Error::Success;
        }

        Error push_front(int data)
        {
            if (!count)
            {
                list_init(data);

                return Error::Success;
            }

            Node *node{new Node()};

            node->next = front;
            node->data = data;
            front->prev = node;

            front = node;

            ++count;
            return Error::Success;
        }

        Error insert(int data, size_t index)
        {
            if (count <= index)
                return Error::Failure;

            Node *temp{get(index)};

            Node *node{new Node()};

            node->data = data;
            node->next = temp;
            node->prev = temp->prev;

            (temp->prev)->next = node;
            temp->prev = node;

            ++count;
            return Error::Success;
        }

        Error remove_back()
        {
            if (!count)
                return Error::Failure;

            Node *temp{back->prev};

            delete back;

            back = temp;

            --count;

            return Error::Success;
        }

        Error remove_front()
        {
            if (!count)
                return Error::Failure;

            Node *temp{front->next};

            delete front;

            front = temp;

            --count;

            return Error::Success;
        }

        Error remove(size_t index)
        {
            if (!count || count <= index)
                return Error::Failure;

            if (index == 0)
            {
                remove_front();
                return Error::Success;
            }

            if (index == count - 1)
            {
                remove_back();
                return Error::Success;
            }

            Node *node{get(index)};
            (node->prev)->next = node->next;
            (node->next)->prev = node->prev;

            delete node;
            node = nullptr;

            --count;

            return Error::Success;
        }

        size_t size() const
        {
            return count;
        }

        int &operator[](size_t index) const
        {
            return get(index)->data;
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

        Node *get(int index) const
        {
            Node *node{front};

            for (int i = 0; i < index; ++i)
                node = node->next;

            return node;
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
            os << list[i] << ", ";
        }
        os << ']' << '\n';

        return os;
    }
}