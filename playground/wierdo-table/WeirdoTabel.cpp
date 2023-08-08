#include "WeirdoTable.h"

size_t WeirdoTable::hash(const std::string &key) const
{
    return static_cast<size_t>(key[key.size() - 1]);
}

size_t WeirdoTable::insert(const std::string &key, int value)
{
    size_t index{hash(key)};

    Node node{key, value, Status::Occupied};

    for (size_t i{0}; i < TABLE_LENGTH; ++i)
    {
        index = (index + i) % TABLE_LENGTH;

        Node &candidate{table[index]};

        if (candidate.status == Status::Available)
            candidate = std::move(node);
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
