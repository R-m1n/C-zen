#pragma once

#include <string>
#include <array>
#include <exception>

#define TABLE_LENGTH 26
#define CHECK_KEY(key_size) (key_size <= 10)

enum class Status
{
    Available = 0,
    Tombstone,
    Occupied
};

template <typename _Table>
class WeirdoIterator
{
public:
    using node_type = typename _Table::node_type;
    using Iterator = typename _Table::Iterator;

    WeirdoIterator(node_type *ptr) : ptr{ptr} {}

    Iterator &operator+=(size_t position)
    {
        return this;
    }

    node_type &operator*()
    {
        return *ptr;
    }

private:
    node_type *ptr;
};

template <typename T>
struct Node
{
    using value_type = T;

    std::string key;
    T value;
    Status status;

    Node() : key{""}, status{Status::Available} {}
    Node(const std::string &key, T value, Status status) : key{key}, value{value}, status{status} {}
};

template <typename T>
class WeirdoTable
{
public:
    using value_type = T;
    using node_type = Node<T>;
    using Iterator = WeirdoIterator<WeirdoTable<T>>;

    bool insert(const std::string &key, const T &value);
    T &operator[](const std::string &key);

    Iterator begin()
    {
        for (auto &node : table)
            if (node.status == Status::Occupied)
                return Iterator(&node);

        return Iterator(&(table[0]));
    }

    Iterator end()
    {
        for (size_t i = table.size() - 1; i >= 0; --i)
            if (table[i].status == Status::Occupied)
                return Iterator(&(table[i]));

        return Iterator(&(table[table.size() - 1]));
    }

private:
    std::array<Node<T>, TABLE_LENGTH> table;

    size_t hash(const std::string &key) const;
};

template <typename T>
bool WeirdoTable<T>::insert(const std::string &key, const T &value)
{
    size_t index{hash(key)};

    Node<T> node(key, value, Status::Occupied);

    for (size_t i{0}; i < TABLE_LENGTH; ++i)
    {
        Node<T> &candidate{table[(index + i) % TABLE_LENGTH]};

        if (candidate.status == Status::Available)
        {
            candidate = std::move(node);
            return true;
        }
    }

    return false;
}

template <typename T>
T &WeirdoTable<T>::operator[](const std::string &key)
{
    size_t index{hash(key)};

    for (size_t i{0}; i < TABLE_LENGTH; ++i)
    {
        Node<T> &candidate{table[(index + i) % TABLE_LENGTH]};

        if (candidate.key == key)
            return candidate.value;
    }

    insert(key, 0);

    return (*this)[key];
}

template <typename T>
size_t WeirdoTable<T>::hash(const std::string &key) const
{
    if (!CHECK_KEY(key.size()))
        throw std::invalid_argument("maximum key length is 10.");

    return static_cast<int>(key[key.size() - 1]) - 97;
}