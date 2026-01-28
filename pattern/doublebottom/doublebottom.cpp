#include "doublebottom.hpp"

// -------------------- Helpers --------------------

bool DoubleBottomDetector::isLocalMin(const std::vector<double>& price, int i) {
    return price[i] < price[i - 1] && price[i] < price[i + 1];
}

// -------------------- Core Logic --------------------

bool DoubleBottomDetector::findDoubleBottom(const std::vector<double>& price) {
    int n = price.size();
    if (n < 6) return false;

    std::vector<int> valleys;

    // Step 1: Find local valleys
    for (int i = 1; i < n - 1; i++) {
        if (isLocalMin(price, i)) {
            valleys.push_back(i);
        }
    }

    if (valleys.size() < 2) return false;

    double tolerance = 0.03;   // 3%

    // Step 2: Compare valley pairs
    for (int k = 0; k + 1 < static_cast<int>(valleys.size()); k++) {
        int v1 = valleys[k];
        int v2 = valleys[k + 1];

        double price1 = price[v1];
        double price2 = price[v2];

        // Step 3: Similar depth check
        double diff = std::abs(price1 - price2) / std::max(price1, price2);
        if (diff > tolerance) continue;

        // Step 4: Peak between valleys
        double peak = price[v1 + 1];
        for (int i = v1 + 1; i < v2; i++) {
            peak = std::max(peak, price[i]);
        }

        if (peak < std::max(price1, price2) * 1.03) continue;

        // Step 5: Confirmation breakout
        if (v2 + 1 < n && price[v2 + 1] > price[v2])
            return true;
    }

    return false;
}

// -------------------- Public API --------------------

PatternResult DoubleBottomDetector::detect(const std::vector<double>& price) {
    bool isDoubleBottom = findDoubleBottom(price);

    PatternResult result;

    result.pattern = PATTERN::DOUBLE_BOTTOM;
    result.trend = isDoubleBottom ? TREND :: BULLISH : TREND :: NEUTRAL;

    return result;
}
