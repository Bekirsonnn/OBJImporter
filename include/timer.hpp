#pragma once

#include <chrono>
#include <iostream>

struct Timer
{
    using Clock = std::chrono::steady_clock;

    Clock::time_point start = Clock::now();

    Timer() = default;

    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;

    ~Timer()
    {
        const auto end = Clock::now();
        const auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::cout << "Time: " << elapsed << " microseconds\n";
    }
};
