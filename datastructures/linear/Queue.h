#pragma once

#include <iostream>
#include <string>
#include <array>

#include "Array.h"
#include "LinkedList.h"
#include "../Exception.h"

namespace cantor
{
    template <typename T, size_t S>
    class Queue
    {
    public:
        using value_type = T;
        using reference_type = T &;
        using temporary_type = T &&;

        constexpr void push(const reference_type value);

        constexpr void push(temporary_type value);

        constexpr value_type pop();

        constexpr reference_type back();

        constexpr reference_type front();

        constexpr size_t capacity() const;

        constexpr size_t size() const;

        constexpr bool empty() const;

        constexpr bool full() const;

    private:
        Array<value_type, S> queue;

        size_t m_front = 0;
        size_t m_back = 0;

        size_t m_count = 0;
    };

    template <typename T, size_t S>
    constexpr void Queue<T, S>::push(const reference_type value)
    {
        if (full())
            throw queue_overflow_error("the queue is full!");

        queue[m_back] = value;

        ++m_count;

        m_back = (m_back + 1) % capacity();
    }

    template <typename T, size_t S>
    constexpr void Queue<T, S>::push(temporary_type value)
    {
        push(value);
    }

    template <typename T, size_t S>
    constexpr T Queue<T, S>::pop()
    {
        if (empty())

            throw empty_queue_error("the queue is empty!");

        value_type temp{queue[m_front]};

        m_front = (m_front + 1) % capacity();

        --m_count;

        return temp;
    }

    template <typename T, size_t S>
    constexpr T &Queue<T, S>::back()
    {
        if (empty())
            throw empty_queue_error("the queue is empty!");

        return queue[m_back];
    }

    template <typename T, size_t S>
    constexpr T &Queue<T, S>::front()
    {
        if (empty())
            throw empty_queue_error("the queue is empty!");

        return queue[m_front];
    }

    template <typename T, size_t S>
    constexpr size_t Queue<T, S>::capacity() const
    {
        return S;
    }

    template <typename T, size_t S>
    constexpr size_t Queue<T, S>::size() const
    {
        return m_count;
    }

    template <typename T, size_t S>
    constexpr bool Queue<T, S>::empty() const
    {
        return m_count == 0;
    }

    template <typename T, size_t S>
    constexpr bool Queue<T, S>::full() const
    {
        return m_count == capacity();
    }

    template <typename T>
    class Deque
    {
    public:
        using value_type = T;
        using reference_type = T &;
        using temporary_type = T &&;
        using pointer_type = T *;

        void push_back(const reference_type value);

        void push_back(temporary_type value);

        void push_front(const reference_type value);

        void push_front(temporary_type value);

        value_type pop();

        reference_type back();

        reference_type front();

        size_t size() const;

        bool empty() const;

    private:
        LinkedList<value_type> queue;

        size_t m_front = 0;
    };

    template <typename T>
    void Deque<T>::push_back(const reference_type value)
    {
        queue.push_back(value);
    }

    template <typename T>
    void Deque<T>::push_back(temporary_type value)
    {
        push_back(value);
    }

    template <typename T>
    void Deque<T>::push_front(const reference_type value)
    {
        queue.push_front(value);
    }

    template <typename T>
    void Deque<T>::push_front(temporary_type value)
    {
        push_front(value);
    }

    template <typename T>
    T Deque<T>::pop()
    {
        value_type temp{queue.get_front()};

        queue.remove_front();

        return temp;
    }

    template <typename T>
    T &Deque<T>::back()
    {
        return queue.get_back();
    }

    template <typename T>
    T &Deque<T>::front()
    {
        return queue.get_front();
    }

    template <typename T>
    size_t Deque<T>::size() const
    {
        return queue.size();
    }

    template <typename T>
    bool Deque<T>::empty() const
    {
        return queue.is_empty();
    }
}
