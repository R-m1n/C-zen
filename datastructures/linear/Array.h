#pragma once

#include <iostream>
#include <stdexcept>

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
        using iterator_reference = iterator &;

        constexpr ArrayIterator(pointer_type value_ptr) : value_ptr{value_ptr} {}

        constexpr pointer_type base()
        {
            return value_ptr;
        }

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

        using iterator = ArrayIterator<ArrayList<T>>;

        ArrayList() : m_array{nullptr}, m_count{0}, m_capacity{0} {}

        ArrayList(size_t n) : m_array{new value_type[n]}, m_count{0}, m_capacity{n} {}

        ArrayList(const ArrayList<value_type> &other)
        {
            *this = other;
        }

        ArrayList(ArrayList<value_type> &&other)
        {
            *this = std::move(other);
        }

        ~ArrayList()
        {
            if (!m_array)
                delete[] m_array;

            m_array = nullptr;
            m_count = 0;
            m_capacity = 0;
        }

        reference_type at(size_t index) const
        {
            return (0 <= index < m_count) ? m_array[index] : throw std::out_of_range("index out of range!");
        }

        reference_type operator[](size_t index) const noexcept
        {
            return m_array[index];
        }

        reference_type front() const noexcept
        {
            return *m_array;
        }

        reference_type back() const noexcept
        {
            return *(m_array + m_count - 1);
        }

        pointer_type data() const noexcept
        {
            return m_array;
        }

        bool is_empty() const noexcept
        {
            return m_count == 0;
        }

        size_t size() const noexcept
        {
            return m_count;
        }

        size_t capacity() const noexcept
        {
            return m_capacity;
        }

        iterator begin() const noexcept
        {
            return iterator(m_array);
        }

        iterator end() const noexcept
        {
            return iterator(m_array + m_count - 1);
        }

        void clear() noexcept
        {
            m_count = 0;
        }

        void reserve(size_t n);

        void push_back(const reference_type value);

        void pop_back();

        void shrik_to_fit();

        ArrayList<value_type> &operator=(const ArrayList<value_type> &other);

        ArrayList<value_type> &operator=(ArrayList<value_type> &&other);

    private:
        pointer_type m_array = nullptr;
        size_t m_count = 0;
        size_t m_capacity = 0;

        void resize();

        void shrink();

        void allocate();
    };

    template <typename T>
    void ArrayList<T>::reserve(size_t n)
    {
        if (n > m_capacity)
        {
            m_array = new value_type[n];
            m_capacity = n;
        }
    }

    template <typename T>
    void ArrayList<T>::push_back(const reference_type value)
    {
        if (m_count == m_capacity)
            resize();

        m_array[m_count++] = value;
    }

    template <typename T>
    void ArrayList<T>::pop_back()
    {
        --m_count;

        if (m_count <= (m_capacity / 2))
            shrink();
    }

    template <typename T>
    void ArrayList<T>::shrik_to_fit()
    {
        m_capacity = m_count;

        allocate();
    }

    template <typename T>
    ArrayList<T> &ArrayList<T>::operator=(const ArrayList<value_type> &other)
    {
        if (this != &other)
        {
            delete[] m_array;

            m_capacity = other.capacity();

            m_array = new value_type[m_capacity];

            std::copy(other.begin().base(), other.end().base(), m_array);

            m_count = other.size();
        }

        return *this;
    }

    template <typename T>
    ArrayList<T> &ArrayList<T>::operator=(ArrayList<value_type> &&other)
    {
        if (this != &other)
        {
            delete[] m_array;

            m_array = other.data();

            m_count = other.size();

            m_capacity = other.capacity();

            other.m_array = nullptr;

            other.m_count = 0;

            other.m_capacity = 0;
        }

        return *this;
    }

    template <typename T>
    void ArrayList<T>::resize()
    {
        m_capacity = (m_capacity * 2) + 1;

        allocate();
    }

    template <typename T>
    void ArrayList<T>::shrink()
    {
        m_capacity = (m_capacity - 1) / 2;

        allocate();
    }

    template <typename T>
    inline void ArrayList<T>::allocate()
    {
        pointer_type temp = new value_type[m_capacity];

        std::copy(m_array, m_array + m_count, temp);

        delete[] m_array;

        m_array = temp;
    }
}