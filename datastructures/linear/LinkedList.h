#pragma once
#include <iostream>
#include "../Error.h"

namespace cantor
{
    template <typename T>
    class LinkedList
    {
    public:
        using value_type = T;

        LinkedList() : front{new Node()}, back{new Node()}, count{0} {};

        ~LinkedList()
        {
            delete front;
            delete back;

            front = nullptr;
            back = nullptr;
            count = 0;
        }

        Error push_back(T data);

        Error push_front(T data);

        Error insert(T data, size_t index);

        Error remove_back();

        Error remove_front();

        Error remove(size_t index);

        size_t size() const
        {
            return count;
        }

        T &operator[](size_t index) const
        {
            return get(index)->data;
        }

    private:
        struct Node
        {
            T data;
            Node *next;
            Node *prev;

            Node() : data{0}, next{nullptr}, prev{nullptr} {}
        };

        void list_init(T data)
        {
            front->data = data;
            back = front;

            ++count;
        }

        Node *get(size_t index) const
        {
            Node *node{front};

            for (size_t i = 0; i < index; ++i)
                node = node->next;

            return node;
        }

        Node *front;
        Node *back;

        size_t count;
    };

    template <typename T>
    Error LinkedList<T>::push_back(T data)
    {
        if (!count)
        {
            list_init(data);

            return Ok;
        }

        Node *node{new Node()};

        node->prev = back;
        node->data = data;
        back->next = node;

        back = node;

        ++count;

        return Ok;
    }

    template <typename T>
    Error LinkedList<T>::push_front(T data)
    {
        if (!count)
        {
            list_init(data);

            return Ok;
        }

        Node *node{new Node()};

        node->next = front;
        node->data = data;
        front->prev = node;

        front = node;

        ++count;
        return Ok;
    }

    template <typename T>
    Error LinkedList<T>::insert(T data, size_t index)
    {
        if (count <= index || index < 0)
            return IndexOutOfRange;

        Node *temp{get(index)};

        Node *node{new Node()};

        node->data = data;
        node->next = temp;
        node->prev = temp->prev;

        (temp->prev)->next = node;
        temp->prev = node;

        ++count;

        return Ok;
    }

    template <typename T>
    Error LinkedList<T>::remove_back()
    {
        if (!count)
            return EmptyContainer;

        Node *temp{back->prev};

        delete back;

        back = temp;

        --count;

        return Ok;
    }

    template <typename T>
    Error LinkedList<T>::remove_front()
    {
        if (!count)
            return EmptyContainer;

        Node *temp{front->next};

        delete front;

        front = temp;

        --count;

        return Ok;
    }

    template <typename T>
    Error LinkedList<T>::remove(size_t index)
    {
        if (!count)
            return EmptyContainer;

        if (count <= index || index < 0)
            return IndexOutOfRange;

        if (index == 0)
        {
            remove_front();
            return Ok;
        }

        if (index == count - 1)
        {
            remove_back();
            return Ok;
        }

        Node *node{get(index)};
        (node->prev)->next = node->next;
        (node->next)->prev = node->prev;

        delete node;
        node = nullptr;

        --count;

        return Ok;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const LinkedList<T> &list)
    {
        os << '[';
        for (size_t i = 0; i < list.size(); i++)
        {
            os << list[i] << ", ";
        }
        os << ']' << '\n';

        return os;
    }
}