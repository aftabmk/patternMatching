#include <bits/stdc++.h>
#include "pattern/doubletop/doubletop.hpp"


int main() {
    std::vector<double> price = {
        100, 105, 110, 107, 102,
        108, 111, 106, 101, 98
    };

    bool found = DoubleTopDetector::detect(price);

    if (found)
        std::cout << "Pattern Found ✅" << std::endl;
    else
        std::cout << "No Pattern ❌" << std::endl;

    return 0;
}
