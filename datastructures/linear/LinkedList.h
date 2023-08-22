#pragma once
#include <iostream>

namespace cantor
{
    enum class Error : short
    {
        None = 0,
        IndexOutOfRange,
        EmptyContainer,
    };

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

        void push_back(value_type value);

        void push_front(value_type value);

        const Error insert(value_type value, size_t index);

        const Error remove_back();

        const Error remove_front();

        const Error remove(size_t index);

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
            value_type value;
            Node *next;
            Node *prev;

            Node() : value{0}, next{nullptr}, prev{nullptr} {}
        };

        void list_init(value_type value)
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
    void LinkedList<T>::push_back(value_type value)
    {
        if (!count)
        {
            list_init(value);

            return;
        }

        Node *node{new Node()};

        node->prev = back;
        node->value = value;
        back->next = node;

        back = node;

        ++count;
    }

    template <typename T>
    void LinkedList<T>::push_front(value_type value)
    {
        if (!count)
        {
            list_init(value);

            return;
        }

        Node *node{new Node()};

        node->next = front;
        node->value = value;
        front->prev = node;

        front = node;

        ++count;
    }

    template <typename T>
    const Error LinkedList<T>::insert(value_type value, size_t index)
    {
        if (count <= index || index < 0)
            return Error::IndexOutOfRange;

        Node *temp{get(index)};

        Node *node{new Node()};

        node->value = value;
        node->next = temp;
        node->prev = temp->prev;

        (temp->prev)->next = node;
        temp->prev = node;

        ++count;

        return Error::None;
    }

    template <typename T>
    const Error LinkedList<T>::remove_back()
    {
        if (!count)
            return Error::EmptyContainer;

        Node *temp{back->prev};

        delete back;

        back = temp;

        --count;

        return Error::None;
    }

    template <typename T>
    const Error LinkedList<T>::remove_front()
    {
        if (!count)
            return Error::EmptyContainer;

        Node *temp{front->next};

        delete front;

        front = temp;

        --count;

        return Error::None;
    }

    template <typename T>
    const Error LinkedList<T>::remove(size_t index)
    {
        if (!count)
            return Error::EmptyContainer;

        if (count <= index || index < 0)
            return Error::IndexOutOfRange;

        if (index == 0)
        {
            remove_front();
            return Error::None;
        }

        if (index == count - 1)
        {
            remove_back();
            return Error::None;
        }

        Node *node{get(index)};
        (node->prev)->next = node->next;
        (node->next)->prev = node->prev;

        delete node;
        node = nullptr;

        --count;

        return Error::None;
    }
}