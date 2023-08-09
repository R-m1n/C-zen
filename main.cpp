#include <iostream>
#include <string>
#include <unordered_map>

#include "playground/wierdo-table/WeirdoTable.h"

int main()
{
    WeirdoTable<int> wt;

    wt.insert("armin", 25);
    wt.insert("arian", 19);
    wt.insert("kiana", 23);

    auto ptr = wt.end();

    std::cout << (*ptr).value;

    // std::unordered_map<std::string, int> map;

    // map["armin"] = 25;
    // map["arian"] = 19;
    // map["kiana"] = 23;

    // for (auto i : map)
    // {
    //     std::cout << i.first;
    //     std::cout << i.second;
    // }

    return 0;
}