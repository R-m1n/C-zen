#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "algorithms/Sorting.h"
#include "algorithms/StackEvens.h"
#include "datastructures/linear/LinkedList.h"
#include "datastructures/linear/Stack.h"
#include "datastructures/linear/Array.h"
#include "utility/Timer.h"

enum class Symbol : char
{
    Plus = '+',
    Minus = '-',
    Multiply = '*',
    Divide = '/',
};

bool operator==(char ch, Symbol sym)
{
    return ch == static_cast<char>(sym);
}

void postfix_eval(const std::string &input)
{
    cantor::StackList<int> operands;
    cantor::StackList<int> reverse_operands;

    int result = 0;

    for (char c : input)
    {
        if ('0' <= c && c <= '9')
        {
            reverse_operands.push(static_cast<int>(c) - '0');

            continue;
        }

        bool is_symbol = c == Symbol::Plus || c == Symbol::Minus || c == Symbol::Multiply || c == Symbol::Divide;

        if (is_symbol)
        {
            while (!reverse_operands.is_empty())
                operands.push(reverse_operands.pop());

            result += operands.pop();

            while (!operands.is_empty())
            {
                if (c == Symbol::Plus)
                    result += operands.pop();

                else if (c == Symbol::Minus)
                    result -= operands.pop();

                else if (c == Symbol::Multiply)
                    result *= operands.pop();

                else if (c == Symbol::Divide)
                    result /= operands.pop();
            }

            reverse_operands.push(result);

            result = 0;
        }
    }

    std::cout << reverse_operands.pop();
}

int count = 0;

template <size_t S>
void backBin(std::array<int, S> &arr, int n)
{
    if (n < 1)
    {
        if ((arr[0] == arr[1]) || (arr[0] == arr[2]) || (arr[1] == arr[2]))
        {
            ++count;

            for (auto ri = arr.crbegin(); ri != arr.crend(); ++ri)
                std::cout << *ri;

            std::cout << '\n';
        }

        return;
    }

    for (int i = 1; i <= 9; i++)
    {
        arr[n - 1] = i;

        backBin(arr, n - 1);
    }
}

int increment(int n)
{
    return n + 1;
}

int main()
{
    // std::vector<int> vec{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    // std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // std::vector<int> vec{8, 2, 10, 1, 9, 5, 4, 3, 6, 7};

    // cantor::StackList<int> stack;
    // stack.push(10);
    // stack.push(20);
    // stack.push(30);
    // stack.push(40);
    // stack.push(50);

    // cantor::StackList<int> stack1 = stack;

    // while (!stack.is_empty())
    //     std::cout << stack.pop() << '\n';

    // while (!stack1.is_empty())
    //     std::cout << stack1.pop() << '\n';

    // double counter = 0;

    // for (double i = 0; i < 1000000000; ++i)
    //     counter += (8 / ((4 * i + 1) * (4 * i + 3)));

    std::string s = "32+1-";

    postfix_eval(s);

    return 0;
}
