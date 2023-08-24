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

        Error push(value_type value)
        {
            if (top_ptr == Capacity)
                return Error::StackOverFlow;

            stack[top_ptr++] = value;

            return Error::None;
        }

        std::pair<std::optional<value_type>, Error> pop()
        {
            if (is_empty())
                return std::make_pair({}, Error::EmptyStack);

            return std::make_pair(stack[--top_ptr], Error::None);
        }

        value_type top()
        {
            return stack[top_ptr - 1];
        }

        size_t size() const
        {
            return top_ptr;
        }

        bool is_empty() const
        {
            return top_ptr == 0;
        }

    private:
        value_type *stack;
        size_t top_ptr;
    };
}