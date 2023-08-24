#pragma once

namespace cantor
{
    enum class Error : short
    {
        None = 0,
        IndexOutOfRange,
        EmptyContainer,
        StackOverFlow,
        EmptyStack,
    };
}