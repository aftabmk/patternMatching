#include <vector>
#include <future>
#include <iostream>

#include "pattern/doubletop/doubletop.hpp"



// Price Provider (separate function)
std::vector<double> getPriceData() {
    return {
        100, 105, 110, 107, 102,
        108, 111, 106, 101, 98
    };
}


//  Pattern Task
PatternResult doubleTopTask(const std::vector<double>& price) {
    return DoubleTopDetector::detect(price);
}


// Engine: creates thread array and runs in parallel
std::vector<PatternResult> runPattern() {

    // Get price data from separate function
    std::vector<double> price = getPriceData();

    // Thread array
    std::vector<std::future<PatternResult>> jobs;

    // Inject parallel jobs into array
    jobs.push_back(std::async(std::launch::async, doubleTopTask, std::cref(price)));

    // (Add more patterns here later)

    // Collect results
    std::vector<PatternResult> results;
    for (auto& job : jobs) 
        results.push_back(job.get());

    return results;
}


int main() {

    std::vector<PatternResult> results = runPattern();

    for (int i = 0; i < (int) results.size(); ++i) {
        results[i].print();
    }

    return 0;
}

