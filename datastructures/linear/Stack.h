#pragma once

#include <iostream>
#include <utility>
#include <optional>
#include "../Error.h"

namespace cantor
{
    template <typename T, size_t Capacity>
    class Stack
    {
    public:
        using value_type = T;

        Stack() : stack{new value_type[Capacity]}, top_ptr{0} {}

        ~Stack()
        {
            delete[] stack;

            stack = nullptr;

            top_ptr = 0;
        }

        Stack(const Stack<value_type, Capacity> &other)
        {
            *this = other;
        }

        Stack(Stack<value_type, Capacity> &&other)
        {
            *this = std::move(other);
        }

        Error push(value_type value);

        std::pair<std::optional<value_type>, Error> pop();

        std::pair<std::optional<value_type>, Error> top() const;

        size_t size() const
        {
            return top_ptr;
        }

        bool is_empty() const
        {
            return top_ptr == 0;
        }

        bool is_full() const
        {
            return top_ptr == Capacity;
        }

        Stack<value_type, Capacity> &operator=(const Stack<value_type, Capacity> &other);

        Stack<value_type, Capacity> &operator=(Stack<value_type, Capacity> &&other);

    private:
        value_type *stack;
        size_t top_ptr;
    };

    template <typename T, size_t Capacity>
    Error Stack<T, Capacity>::push(value_type value)
    {
        if (is_full())
            return Error::StackOverFlow;

        stack[top_ptr++] = value;

        return Error::None;
    }

    template <typename T, size_t Capacity>
    std::pair<std::optional<T>, Error> Stack<T, Capacity>::pop()
    {
        if (is_empty())
            return std::make_pair(std::make_optional<T>(), Error::EmptyStack);

        return std::make_pair(stack[--top_ptr], Error::None);
    }

    template <typename T, size_t Capacity>
    std::pair<std::optional<T>, Error> Stack<T, Capacity>::top() const
    {
        if (is_empty())
            return std::make_pair(std::make_optional<T>(), Error::EmptyStack);

        return std::make_pair(stack[top_ptr - 1], Error::None);
    }

    template <typename T, size_t Capacity>
    Stack<T, Capacity> &Stack<T, Capacity>::operator=(const Stack<T, Capacity> &other)
    {
        if (this != &other)
        {
            delete[] stack;

            stack = new value_type[Capacity];

            std::copy(other.stack, other.stack + other.top_ptr, stack);

            top_ptr = other.top_ptr;
        }

        return *this;
    }

    template <typename T, size_t Capacity>
    Stack<T, Capacity> &Stack<T, Capacity>::operator=(Stack<T, Capacity> &&other)
    {
        if (this != &other)
        {
            delete[] stack;

            stack = other.stack;

            top_ptr = other.top_ptr;

            other.stack = nullptr;

            other.top_ptr = 0;
        }

        return *this;
    }
}