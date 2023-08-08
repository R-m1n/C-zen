#pragma once

#include <string>
#include <array>

#define TABLE_LENGTH 26
#define MAX_KEY_LENGTH 10

template <typename _Val>
class WeirdoTable
{
public:
    size_t hash(const std::string &key) const;
    size_t insert(const std::string &key, _Val value);
    _Val &operator[](const std::string &key);

private:
    enum class Status
    {
        Available = 0,
        Tombstone,
        Occupied
    };

    struct Node
    {
        std::string key;
        _Val value;
        Status status;

        Node() : key{""}, status{Status::Available} {}
        Node(const std::string &key, _Val value, Status status) : key{key}, value{value}, status{status} {}
    };

    std::array<Node, TABLE_LENGTH> table;
};

template <typename _Val>
size_t WeirdoTable<_Val>::hash(const std::string &key) const
{
    return static_cast<int>(key[key.size() - 1]) - 97;
}

template <typename _Val>
size_t WeirdoTable<_Val>::insert(const std::string &key, _Val value)
{
    size_t index{hash(key)};

    Node node(key, value, Status::Occupied);

    for (size_t i{0}; i < TABLE_LENGTH; ++i)
    {
        index = (index + i) % TABLE_LENGTH;

        Node &candidate{table[index]};

        if (candidate.status == Status::Available)
        {
            candidate = std::move(node);
            break;
        }
    }

    return index;
}

template <typename _Val>
_Val &WeirdoTable<_Val>::operator[](const std::string &key)
{
    size_t index{hash(key)};

    for (size_t i{0}; i < TABLE_LENGTH; ++i)
    {
        Node &candidate{table[(index + i) % TABLE_LENGTH]};

        if (candidate.key == key)
            return candidate.value;
    }

    index = insert(key, 0);

    return table[index].value;
}
