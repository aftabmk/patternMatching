#include "doubletop.hpp"

bool DoubleTopDetector::isLocalMax(const std::vector<double> &price, int i) {
    return price[i] > price[i-1] && price[i] > price[i+1];
}

bool DoubleTopDetector::findDoubleTop(const std::vector<double>& price) {
    int n = price.size();
    if (n < 6) return false;

    std::vector<int> peaks;

    // Step 1: Find local peaks
    for (int i = 1; i < n - 1; i++) {
        if (isLocalMax(price, i)) {
            peaks.push_back(i);
        }
    }

    if (peaks.size() < 2) return false;

    double tolerance = 0.03;   // 3%

    // Step 2: Compare peak pairs
    for (int k = 0; k + 1 < static_cast<int>(peaks.size()); k++) {
        int p1 = peaks[k];
        int p2 = peaks[k + 1];

        double price1 = price[p1];
        double price2 = price[p2];

        // Step 3: Similar height check
        double diff = abs(price1 - price2) / std::max(price1, price2);
        if (diff > tolerance) continue;

        // Step 4: Valley check
        double valley = price[p1 + 1];
        for (int i = p1 + 1; i < p2; i++) {
            valley = std::min(valley, price[i]);
        }

        if (valley > std::min(price1, price2) * 0.97) continue;

        // Step 5: Confirmation drop
        if (p2 + 1 < n && price[p2 + 1] < price[p2]) 
            return true;
    }

    return false;
}

PatternResult DoubleTopDetector::detect(const std::vector<double>& price) {
    bool isDoubleTop = findDoubleTop(price);

    PatternResult result;

    result.pattern = PATTERN :: DOUBLE_TOP;
    result.trend = isDoubleTop ? TREND ::BEARISH : TREND :: NEUTRAL;

    return result;
}

