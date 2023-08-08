#pragma once

#include <string>
#include <array>

#define TABLE_LENGTH 26
#define MAX_KEY_LENGTH 10

class WeirdoTable
{
public:
    size_t hash(const std::string &key) const;
    size_t insert(const std::string &key, int value);
    int &operator[](const std::string &key);

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
        int value;
        Status status;

        Node() : key{""}, value{0}, status{Status::Available} {}
        Node(const std::string &key, int value, Status status) : key{key}, value{value}, status{status} {}
    };

    std::array<Node, TABLE_LENGTH> table;
};

size_t WeirdoTable::hash(const std::string &key) const
{
    return static_cast<int>(key[key.size() - 1]) - 97;
}

size_t WeirdoTable::insert(const std::string &key, int value)
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

int &WeirdoTable::operator[](const std::string &key)
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
