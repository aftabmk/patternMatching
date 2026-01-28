#include <iostream>
#include "worker/worker.hpp"

int main() {

    auto workers = runParallelPatterns();

    for (auto& worker : workers) {
        worker.print();
    }

    return 0;
}
