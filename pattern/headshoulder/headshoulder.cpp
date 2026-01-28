#include "headshoulder.hpp"

#include <cmath>
#include <algorithm>

// ---------------- Helpers ----------------

bool HeadShoulderDetector::isLocalMax(const std::vector<double>& price, int i) {
    return price[i] > price[i - 1] && price[i] > price[i + 1];
}

// ---------------- Core Logic ----------------

bool HeadShoulderDetector::findPattern(const std::vector<double>& price) {
    int n = price.size();
    if (n < 7) return false;

    std::vector<int> peaks;

    for (int i = 1; i < n - 1; ++i) {
        if (isLocalMax(price, i))
            peaks.push_back(i);
    }

    if (peaks.size() < 3) return false;

    double shoulderTolerance = 0.05;

    for (int i = 0; i + 2 < (int)peaks.size(); ++i) {
        int L = peaks[i];
        int H = peaks[i + 1];
        int R = peaks[i + 2];

        double left  = price[L];
        double head  = price[H];
        double right = price[R];

        // Head must be highest
        if (!(head > left && head > right)) continue;

        // Shoulders must be similar height
        double diff = std::abs(left - right) / std::max(left, right);
        if (diff > shoulderTolerance) continue;

        // Neckline break confirmation
        if (R + 1 < n && price[R + 1] < right)
            return true;
    }

    return false;
}

// ---------------- Public API ----------------

PatternResult HeadShoulderDetector::detect(const std::vector<double>& price) {

    bool found = findPattern(price), context = nearRecentMax(price);

    PatternResult result;
    result.pattern = PATTERN :: HEAD_SHOULDER;
    result.trend   = found && context ? TREND :: BEARISH : TREND :: NEUTRAL;

    return result;
}
