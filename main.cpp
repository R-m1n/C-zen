#include <iostream>
#include <string>
#include <unordered_map>

#include "playground/wierdo-table/WeirdoTable.h"

int main()
{
    WeirdoTable<int> wt;

    wt.insert("armin", 25);
    wt.insert("arian", 19);
    wt.insert("kianai", 23);

    for (auto &[key, value, status] : wt)
    {
        std::cout << key << ": " << value << '\n';
    }

    // std::unordered_map<std::string, int> map;

    // map["armin"] = 25;
    // map["arian"] = 19;
    // map["kiana"] = 23;

    return 0;
}