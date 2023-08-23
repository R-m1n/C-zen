#pragma once

#include <chrono>
#include <iostream>

namespace util
{
    class Timer
    {
    public:
        Timer() : start{std::chrono::high_resolution_clock::now()} {}

        ~Timer()
        {
            std::chrono::duration<double, std::milli> duration = std::chrono::high_resolution_clock::now() - start;

            std::cout << duration.count() << "ms" << '\n';
        }

    private:
        std::chrono::system_clock::time_point start;
    };
}