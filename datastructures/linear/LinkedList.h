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

        value_type &operator*()
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

    template <typename List>
    class ReverseListIterator
    {
    public:
        using iterator = ListIterator<List>;
        using value_type = typename iterator::value_type;

        ReverseListIterator() = delete;

        value_type &operator++()
        {
            --iter;

            return *iter;
        }

        value_type operator++(int)
        {
            value_type temp{*iter};

            --iter;

            return temp;
        }

        value_type &operator--()
        {
            ++iter;

            return *iter;
        }

        value_type operator--(int)
        {
            value_type temp{*iter};

            ++iter;

            return temp;
        }

        value_type operator+(int n)
        {
            for (int i = 0; i < n; ++i)
                --iter;

            return *iter;
        }

        value_type operator-(int n)
        {
            for (int i = 0; i < n; ++i)
                ++iter;

            return *iter;
        }

        bool operator==(ReverseListIterator<List> other)
        {
            return iter == other.iter;
        }

        bool operator!=(ReverseListIterator<List> other)
        {
            return !(*this == other);
        }

        value_type operator*()
        {
            return *iter;
        }

        template <typename T>
        friend class LinkedList;

    private:
        ReverseListIterator(iterator iter) : iter{iter} {}

        iterator iter;
    };

    template <typename T>
    class LinkedList
    {
    public:
        using value_type = T;
        using reference_type = T &;
        using temporary_type = T &&;
        using pointer_type = T *;

        using iterator = ListIterator<LinkedList<T>>;
        using reverse_iterator = ReverseListIterator<LinkedList<T>>;

        LinkedList() : front{nullptr}, back{nullptr}, count{0} {};

        LinkedList(const LinkedList<T> &list)
        {
            *this = list;
        };

        LinkedList(LinkedList<T> &&list)
        {
            *this = std::move(list);
        };

        LinkedList(std::initializer_list<T> list)
        {
            for (const auto &item : list)
                push_back(item);
        };

        ~LinkedList()
        {
            clear();
        }

        void push_back(temporary_type value)
        {
            push_back(value);
        }

        void push_front(temporary_type value)
        {
            push_front(value);
        }

        const reference_type get_back() const
        {
            return back->value;
        }

        const reference_type get_front() const
        {
            return front->value;
        }

        void push_back(const reference_type value);

        void push_front(const reference_type value);

        const Error insert(value_type value, size_t index);

        const Error remove_back();

        const Error remove_front();

        const Error remove(size_t index);

        void clear();

        void reverse();

        iterator begin() const
        {
            return iterator(front);
        }

        iterator end() const
        {
            return iterator(back->next);
        }

        reverse_iterator rbegin() const
        {
            return reverse_iterator(iterator(back));
        }

        reverse_iterator rend() const
        {
            return reverse_iterator(iterator(front->prev));
        }

        size_t size() const
        {
            return count;
        }

        bool is_empty() const
        {
            return count == 0;
        }

        reference_type operator[](size_t index) const
        {
            return get(index)->value;
        }

        LinkedList<T> &operator=(const LinkedList<T> &list);

        LinkedList<T> &operator=(LinkedList<T> &&list);

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

        void reverse(Node *node, Node *next);

        Node *front;
        Node *back;

        size_t count;
    };

    template <typename T>
    void LinkedList<T>::push_back(const reference_type value)
    {
        if (is_empty())
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
    void LinkedList<T>::push_front(const reference_type value)
    {
        if (is_empty())
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
        if (is_empty())
            return Error::EmptyList;

        if (index < 0 || index > count)
            return Error::IndexOutOfRange;

        if (index == 0)
        {
            push_front(value);

            return Error::None;
        }

        if (index == count)
        {
            push_back(value);

            return Error::None;
        }

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
        if (is_empty())
            return Error::EmptyList;

        if (count == 1)
        {
            delete back;

            back = nullptr;
            front = nullptr;

            --count;

            return Error::None;
        }

        Node *temp{back->prev};

        delete back;

        back = temp;

        --count;

        return Error::None;
    }

    template <typename T>
    const Error LinkedList<T>::remove_front()
    {
        if (is_empty())
            return Error::EmptyList;

        if (count == 1)
        {
            delete front;

            front = nullptr;
            back = nullptr;

            --count;

            return Error::None;
        }

        Node *temp{front->next};

        delete front;

        front = temp;

        --count;

        return Error::None;
    }

    template <typename T>
    const Error LinkedList<T>::remove(size_t index)
    {
        if (is_empty())
            return Error::EmptyList;

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

        --count;

        return Error::None;
    }

    template <typename T>
    void LinkedList<T>::clear()
    {
        if (count % 2 != 0)
            remove_front();

        if (is_empty())
            return;

        Node *tobe_front = front->next;
        Node *tobe_back = back->prev;

        while (count)
        {
            delete front;
            delete back;

            front = tobe_front;
            back = tobe_back;

            tobe_front = front->next;
            tobe_back = back->prev;

            count -= 2;
        }

        front = nullptr;
        back = nullptr;
    }

    template <typename T>
    void LinkedList<T>::reverse()
    {
        if (is_empty() || count == 1)
            return;

        if (count == 2)
        {
            back->prev = nullptr;
            back->next = front;

            front->prev = back;
            front->next = nullptr;

            std::swap(back, front);

            return;
        }

        reverse(front, front->next);
    }

    template <typename T>
    LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &list)
    {
        if (this != &list)
        {
            clear();

            for (const auto &item : list)
                push_back(item);
        }

        return *this;
    }

    template <typename T>
    LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> &&list)
    {
        if (this != &list)
        {
            clear();

            front = list.front;
            back = list.back;

            count = list.count;

            list.front = nullptr;
            list.back = nullptr;

            list.count = 0;
        }

        return *this;
    }

    template <typename T>
    void LinkedList<T>::reverse(Node *node, Node *next)
    {
        if (next == back)
        {
            next->prev = nullptr;

            next->next = node;

            node->prev = next;

            front = next;

            return;
        }

        reverse(next, next->next);

        next->next = node;

        node->prev = next;

        back = node;

        back->next = nullptr;
    }
}