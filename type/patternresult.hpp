#pragma once
#include <string>
#include <iomanip>
#include <iostream>

struct PatternResult {
    std::string trend, pattern;

    void print(const int padding = 10) const {
        int PAD = padding;

        std::cout << "{\n";
        std::cout << "  " << std::left << std::setw(PAD) << "pattern"
                  << ": " << pattern << "\n";
        std::cout << "  " << std::left << std::setw(PAD) << "trend"
                  << ": " << trend << "\n";
        std::cout << "}\n";
    }
};
