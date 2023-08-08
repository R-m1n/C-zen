#pragma once

#include <string>
#include <array>

#define TABLE_LENGTH 26
#define MAX_KEY_LENGTH 10

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
    Status status{Status::Available};

    Node(const std::string &key, int value, Status status) : key{key}, value{value}, status{status} {}
};

class WeirdoTable
{
public:
    size_t hash(const std::string &key) const;
    size_t insert(const std::string &key, int value);
    Node &operator[](const std::string &key);

private:
    std::array<Node, TABLE_LENGTH> table;
};