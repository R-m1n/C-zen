#pragma once
#include <iostream>
#include "../Error.h"

namespace cantor
{
    template <typename List>
    class ListIterator
    {
    public:
        using value_type = typename List::value_type;

        ListIterator() = delete;

        value_type &operator++()
        {
            node = node->next;

            return node->value;
        }

        value_type operator++(int)
        {
            value_type temp{node->value};

            node = node->next;

            return temp;
        }

        value_type &operator--()
        {
            node = node->prev;

            return node->value;
        }

        value_type operator--(int)
        {
            value_type temp{node->value};

            node = node->prev;

            return temp;
        }

        value_type operator+(int n)
        {
            for (int i = 0; i < n; ++i)
                node = node->next;

            return node->value;
        }

        value_type operator-(int n)
        {
            for (int i = 0; i < n; ++i)
                node = node->prev;

            return node->value;
        }

        bool operator==(ListIterator<List> other)
        {
            return node == other.node;
        }

        bool operator!=(ListIterator<List> other)
        {
            return !(*this == other);
        }

        value_type operator*()
        {
            return node->value;
        }

        template <typename T>
        friend class LinkedList;

    private:
        using Node = typename List::Node;

        ListIterator(Node *node) : node{node} {}

        Node *node;
    };

    template <typename T>
    class LinkedList
    {
    public:
        using value_type = T;
        using iterator = ListIterator<LinkedList<T>>;

        LinkedList() : front{nullptr}, back{nullptr}, count{0} {};

        ~LinkedList()
        {
            delete front;
            delete back;

            front = nullptr;
            back = nullptr;
            count = 0;
        }

        Error push_back(T value);

        Error push_front(T value);

        Error insert(T value, size_t index);

        Error remove_back();

        Error remove_front();

        Error remove(size_t index);

        iterator begin() const
        {
            return iterator(front);
        }

        iterator end() const
        {
            return iterator(back->next);
        }

        size_t size() const
        {
            return count;
        }

        T &operator[](size_t index) const
        {
            return get(index)->value;
        }

        template <typename List>
        friend class ListIterator;

    private:
        struct Node
        {
            T value;
            Node *next;
            Node *prev;

            Node() : value{0}, next{nullptr}, prev{nullptr} {}
        };

        void list_init(T value)
        {
            front = new Node();

            front->value = value;
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
    Error LinkedList<T>::push_back(T value)
    {
        if (!count)
        {
            list_init(value);

            return Ok;
        }

        Node *node{new Node()};

        node->prev = back;
        node->value = value;
        back->next = node;

        back = node;

        ++count;

        return Ok;
    }

    template <typename T>
    Error LinkedList<T>::push_front(T value)
    {
        if (!count)
        {
            list_init(value);

            return Ok;
        }

        Node *node{new Node()};

        node->next = front;
        node->value = value;
        front->prev = node;

        front = node;

        ++count;
        return Ok;
    }

    template <typename T>
    Error LinkedList<T>::insert(T value, size_t index)
    {
        if (count <= index || index < 0)
            return IndexOutOfRange;

        Node *temp{get(index)};

        Node *node{new Node()};

        node->value = value;
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