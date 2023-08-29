#include <stdexcept>

namespace cantor
{
    class queue_overflow_error : public std::runtime_error
    {
    public:
        explicit queue_overflow_error(const char *msg) : std::runtime_error(msg){};
        explicit queue_overflow_error(std::string msg) : std::runtime_error(msg){};
    };

    class empty_queue_error : public std::runtime_error
    {
    public:
        explicit empty_queue_error(const char *msg) : std::runtime_error(msg){};
        explicit empty_queue_error(std::string msg) : std::runtime_error(msg){};
    };
}