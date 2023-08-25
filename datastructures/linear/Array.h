#pragma once

#include <iostream>

namespace cantor
{
    template <typename Array>
    class ArrayIterator
    {
    public:
        using value_type = typename Array::value_type;
        using iterator = ArrayIterator<Array>;

        ArrayIterator(value_type *value_ptr) : value_ptr{value_ptr} {}

        iterator &operator++()
        {
            ++value_ptr;

            return *this;
        }

        iterator operator++(int)
        {
            iterator temp{*this};

            ++value_ptr;

            return temp;
        }

        iterator &operator--()
        {
            --value_ptr;

            return *this;
        }

        iterator operator--(int)
        {
            iterator temp{*this};

            --value_ptr;

            return temp;
        }

        iterator &operator+=(int n)
        {
            value_ptr += n;

            return *this;
        }

        iterator &operator-=(int n)
        {
            value_ptr -= n;

            return *this;
        }

        iterator operator+(int n)
        {
            return iterator(value_ptr + n);
        }

        iterator operator-(int n)
        {
            return iterator(value_ptr - n);
        }

        value_type &operator*()
        {
            return *value_ptr;
        }

        bool operator==(const iterator &other)
        {
            return value_ptr == other.value_ptr;
        }

        bool operator!=(const iterator &other)
        {
            return !(*this == other);
        }

    private:
        value_type *value_ptr;
    };

    template <typename T, size_t S>
    class Array
    {
    public:
        using value_type = T;
        using iterator = ArrayIterator<Array<T, S>>;

        constexpr size_t size() const
        {
            return S;
        }

        value_type &operator[](size_t index)
        {
            return array[index];
        }

        iterator begin()
        {
            return iterator(array);
        }

        iterator end()
        {
            return iterator(array + size());
        }

    private:
        value_type array[S];
    };
}