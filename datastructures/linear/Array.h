#pragma once

#include <iostream>

namespace cantor
{
    template <typename Array>
    class ArrayIterator
    {
    public:
        using value_type = typename Array::value_type;
        using reference_type = value_type &;
        using pointer_type = value_type *;

        using iterator = ArrayIterator<Array>;
        using iterator_reference = ArrayIterator<Array>;

        constexpr ArrayIterator(pointer_type value_ptr) : value_ptr{value_ptr} {}

        constexpr iterator_reference operator++()
        {
            ++value_ptr;

            return *this;
        }

        constexpr iterator operator++(int)
        {
            iterator temp{*this};

            ++value_ptr;

            return temp;
        }

        constexpr iterator_reference operator--()
        {
            --value_ptr;

            return *this;
        }

        constexpr iterator operator--(int)
        {
            iterator temp{*this};

            --value_ptr;

            return temp;
        }

        constexpr iterator_reference operator+=(int n)
        {
            value_ptr += n;

            return *this;
        }

        constexpr iterator_reference operator-=(int n)
        {
            value_ptr -= n;

            return *this;
        }

        constexpr iterator operator+(int n)
        {
            return iterator(value_ptr + n);
        }

        constexpr iterator operator-(int n)
        {
            return iterator(value_ptr - n);
        }

        constexpr reference_type operator*()
        {
            return *value_ptr;
        }

        constexpr bool operator==(const iterator &other)
        {
            return value_ptr == other.value_ptr;
        }

        constexpr bool operator!=(const iterator &other)
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
        using reference_type = T &;
        using temporary_type = T &&;
        using pointer_type = T *;

        using iterator = ArrayIterator<Array<T, S>>;

        constexpr reference_type front() const noexcept
        {
            return array[0];
        }

        constexpr reference_type back() const noexcept
        {
            return array[size() - 1];
        }

        constexpr pointer_type data() const noexcept
        {
            return array;
        }

        constexpr void fill(const reference_type value) noexcept
        {
            for (auto &&i : array)
                i = value;
        }

        constexpr void fill(temporary_type value) noexcept
        {
            fill(value);
        }

        constexpr size_t size() const noexcept
        {
            return S;
        }

        constexpr iterator begin() const noexcept
        {
            return iterator(const_cast<pointer_type>(array));
        }

        constexpr iterator end() const noexcept
        {
            return iterator(const_cast<pointer_type>(array) + size());
        }

        constexpr iterator begin() noexcept
        {
            return iterator(array);
        }

        constexpr iterator end() noexcept
        {
            return iterator(array + size());
        }

        constexpr reference_type operator[](size_t index) const noexcept
        {
            return array[index];
        }

    private:
        value_type array[S];
    };

    template <typename T>
    class ArrayList
    {
    public:
        using value_type = T;
        using reference_type = value_type &;
        using temporary_type = value_type &&;
        using pointer_type = value_type *;

        using iterator = ArrayIterator<Array<T, S>>;

        reference_type front() const noexcept
        {
            return array[0];
        }

        reference_type back() const noexcept
        {
            return array[size() - 1];
        }

        pointer_type data() const noexcept
        {
            return array;
        }

        void fill(const reference_type value) noexcept
        {
            for (auto &&i : array)
                i = value;
        }

        void fill(temporary_type value) noexcept
        {
            fill(value);
        }

        constexpr size_t size() const noexcept
        {
            return S;
        }

        constexpr iterator begin() const noexcept
        {
            return iterator(const_cast<pointer_type>(array));
        }

        constexpr iterator end() const noexcept
        {
            return iterator(const_cast<pointer_type>(array) + size());
        }

        constexpr iterator begin() noexcept
        {
            return iterator(array);
        }

        constexpr iterator end() noexcept
        {
            return iterator(array + size());
        }

        constexpr reference_type operator[](size_t index) const noexcept
        {
            return array[index];
        }

    private:
        value_type array[S];
    };
}