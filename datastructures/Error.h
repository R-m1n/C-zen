#pragma once

namespace cantor
{
    enum class ErrorType : short
    {
        None = 0,
        IndexOutOfRange,
        EmptyContainer,
    };

    struct Error
    {
        ErrorType type;

        const char *msg;

        Error(ErrorType type, const char *msg) : type{type}, msg{msg} {}
    };

    const Error Ok{ErrorType::None, ""};
    const Error IndexOutOfRange{ErrorType::IndexOutOfRange, "Index should be inside the container range."};
    const Error EmptyContainer{ErrorType::EmptyContainer, "The list is empty."};
}