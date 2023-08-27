#pragma once
#include <string>

namespace cantor
{
    bool check_symbol_balance(const std::string &input);
    void infix_to_postfix(const std::string &input);
    void postfix_eval(const std::string &input);
}