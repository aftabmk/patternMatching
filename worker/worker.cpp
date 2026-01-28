#include "worker.hpp"

#include <future>

#include "../data/price_provider.hpp"

#include "../pattern/headshoulder/headshoulder.hpp"
#include "../pattern/doublepattern/doublepattern.hpp"
#include "../pattern/inverseheadshoulder/inverseheadshoulder.hpp"
// ---------------- Pattern Tasks ----------------

PatternResult headShoulderTask(const std::vector<double>& price) {
    return HeadShoulderDetector::detect(price);
}

PatternResult inverseHeadShoulder(const std::vector<double>& price) {
    return InverseHeadShoulderDetector::detect(price);
}

PatternResult doublePattern(const std::vector<double>& price) {
    return DoublePatternDetector::detect(price);
}

// ---------------- Parallel Runner ----------------

std::vector<PatternResult> runParallelPatterns() {

    std::vector<double> price = getPriceData();

    std::vector<std::future<PatternResult>> jobs;

    jobs.push_back(
        std::async(std::launch::async, doublePattern, std::cref(price))
    );

    jobs.push_back(
        std::async(std::launch::async, headShoulderTask, std::cref(price))
    );
    
    jobs.push_back(
        std::async(std::launch::async, inverseHeadShoulder, std::cref(price))
    );

    std::vector<PatternResult> results;
    for (auto& job : jobs) {
        results.push_back(job.get());
    }

    return results;
}
