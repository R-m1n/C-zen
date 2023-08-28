#pragma once

#include <iostream>
#include <utility>
#include <optional>
#include <stdexcept>
#include "Array.h"
#include "LinkedList.h"

namespace cantor
{
    template <typename T, size_t S>
    class Stack
    {
    public:
        using value_type = T;
        using reference_type = T &;
        using temporary_type = T &&;
        using pointer_type = T *;

        constexpr void push(const reference_type value);

        constexpr void push(temporary_type value);

        constexpr value_type pop() noexcept;

        constexpr value_type top() const noexcept;

        constexpr size_t size() const noexcept
        {
            return top_ptr;
        }

        constexpr bool is_empty() const noexcept
        {
            return top_ptr == 0;
        }

        constexpr bool is_full() const noexcept
        {
            return top_ptr == S;
        }

    private:
        cantor::Array<value_type, S> stack;
        size_t top_ptr = 0;
    };

    template <typename T, size_t S>
    constexpr void Stack<T, S>::push(const reference_type value)
    {
        if (is_full())
            throw std::length_error("stack is full!");

        stack[top_ptr++] = value;
    }

    template <typename T, size_t S>
    constexpr void Stack<T, S>::push(temporary_type value)
    {
        push(value);
    }

    template <typename T, size_t S>
    constexpr T Stack<T, S>::pop() noexcept
    {
        return stack[--top_ptr];
    }

    template <typename T, size_t S>
    constexpr T Stack<T, S>::top() const noexcept
    {
        return stack[top_ptr - 1];
    }

    template <typename T>
    class StackArray
    {
    public:
        using value_type = T;
        using reference_type = T &;
        using temporary_type = T &&;
        using pointer_type = T *;

        StackArray() {}

        StackArray(size_t n)
        {
            stack.reserve(n);
        }

        StackArray(const StackArray<value_type> &other)
        {
            *this = other;
        }

        StackArray(StackArray<value_type> &&other)
        {
            *this = std::move(other);
        }

        void push(temporary_type value)
        {
            push(value);
        }

        void push(const reference_type value)
        {
            stack.push_back(value);
        }

        value_type pop()
        {
            value_type temp = top();

            stack.pop_back();

            return temp;
        }

        const reference_type top() const
        {
            return stack.back();
        }

        size_t size() const
        {
            return stack.size();
        }

        bool is_empty() const
        {
            return stack.is_empty();
        }

        StackArray<value_type> &operator=(const StackArray<value_type> &other)
        {
            if (this != &other)
                stack = other.stack;

            return *this;
        }

        StackArray<value_type> &operator=(StackArray<value_type> &&other)
        {
            if (this != &other)
                stack = std::move(other.stack);

            return *this;
        }

    private:
        cantor::ArrayList<value_type> stack;
    };

    template <typename T>
    class StackList
    {
    public:
        using value_type = T;
        using reference_type = T &;
        using temporary_type = T &&;
        using pointer_type = T *;

        StackList() {}

        StackList(const StackList<value_type> &other)
        {
            *this = other;
        }

        StackList(StackList<value_type> &&other)
        {
            *this = std::move(other);
        }

        void push(temporary_type value)
        {
            push(value);
        }

        void push(const reference_type value)
        {
            stack.push_back(value);
        }

        value_type pop()
        {
            value_type temp = top();

            stack.remove_back();

            return temp;
        }

        const reference_type top() const
        {
            return stack.get_back();
        }

        size_t size() const
        {
            return stack.size();
        }

        bool is_empty() const
        {
            return stack.is_empty();
        }

        StackList<value_type> &operator=(const StackList<value_type> &other)
        {
            if (this != &other)
                stack = other.stack;

            return *this;
        }

        StackList<value_type> &operator=(StackList<value_type> &&other)
        {
            if (this != &other)
                stack = std::move(other.stack);

            return *this;
        }

    private:
        cantor::LinkedList<value_type> stack;
    };
}