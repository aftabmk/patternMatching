#include "inverseheadshoulder.hpp"
#include <algorithm>
#include <cmath>

// ---------------- Helpers ----------------

bool InverseHeadShoulderDetector::isLocalMin(const std::vector<double>& price, int i) {
    return price[i] < price[i - 1] && price[i] < price[i + 1];
}

// ---------------- Core Logic ----------------

bool InverseHeadShoulderDetector::findPattern(const std::vector<double>& price) {
    int n = price.size();
    if (n < 7) return false;

    std::vector<int> valleys;

    for (int i = 1; i < n - 1; ++i) {
        if (isLocalMin(price, i))
            valleys.push_back(i);
    }

    if (valleys.size() < 3) return false;

    double shoulderTolerance = 0.05;

    for (int i = 0; i + 2 < (int)valleys.size(); ++i) {
        int L = valleys[i];
        int H = valleys[i + 1];
        int R = valleys[i + 2];

        double left  = price[L];
        double head  = price[H];
        double right = price[R];

        // Head must be lowest
        if (!(head < left && head < right)) continue;

        // Shoulders similar depth
        double diff = std::abs(left - right) / std::max(left, right);
        if (diff > shoulderTolerance) continue;

        // Breakout confirmation
        if (R + 1 < n && price[R + 1] > right)
            return true;
    }

    return false;
}

// ---------------- Public API ----------------

PatternResult InverseHeadShoulderDetector::detect(const std::vector<double>& price) {

    bool found = findPattern(price), context = nearRecentMin(price);

    PatternResult result;
	
    result.pattern = PATTERN :: INVERSE_HEAD_SHOULDER;
    result.trend   = found && context ? TREND :: BULLISH : TREND :: NEUTRAL;

    return result;
}
