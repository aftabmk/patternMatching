#include <iostream>
#include "parallel/pattern_parallel.hpp"

int main() {

    auto workers = runParallelPatterns();

    for (auto& worker : workers) {
        worker.print();
    }

    return 0;
}
