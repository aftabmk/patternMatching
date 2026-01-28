#include "pattern_parallel.hpp"

#include <future>

#include "../data/price_provider.hpp"
#include "../pattern/doubletop/doubletop.hpp"
#include "../pattern/doublebottom/doublebottom.hpp"

// ---------------- Pattern Tasks ----------------

PatternResult doubleTopTask(const std::vector<double>& price) {
    return DoubleTopDetector::detect(price);
}

PatternResult doubleBottomTask(const std::vector<double>& price) {
    return DoubleBottomDetector::detect(price);
}

// ---------------- Parallel Runner ----------------

std::vector<PatternResult> runParallelPatterns() {

    std::vector<double> price = getPriceData();

    std::vector<std::future<PatternResult>> jobs;

    jobs.push_back(
        std::async(std::launch::async, doubleTopTask, std::cref(price))
    );

    jobs.push_back(
        std::async(std::launch::async, doubleBottomTask, std::cref(price))
    );

    std::vector<PatternResult> results;
    for (auto& job : jobs) {
        results.push_back(job.get());
    }

    return results;
}
