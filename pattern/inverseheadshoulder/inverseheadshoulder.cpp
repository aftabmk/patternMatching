#include "inverseheadshoulder.hpp"
#include <cmath>
#include <algorithm>

bool InverseHeadShoulderDetector::isLocalMax(const std::vector<double>& p, int i) {
    return p[i] > p[i-1] && p[i] > p[i+1];
}

bool InverseHeadShoulderDetector::isLocalMin(const std::vector<double>& p, int i) {
    return p[i] < p[i-1] && p[i] < p[i+1];
}

// simple slope between two points
static double slope(int x1, double y1, int x2, double y2) {
    return (y2 - y1) / (double)(x2 - x1);
}


bool InverseHeadShoulderDetector::findInverseHeadShoulder(
    const std::vector<double>& price,
    double headRatioBefore,
    double headRatioAfter,
    double maxNeckSlope
) {
    const int n = price.size();
    if (n < 10) return false;

    std::vector<int> troughs;   // local MINs
    std::vector<int> peaks;     // local MAXs

    // --- find local troughs and peaks ---
    for (int i = 1; i < n - 1; ++i) {
        if (isLocalMin(price, i)) troughs.push_back(i);
        if (isLocalMax(price, i)) peaks.push_back(i);
    }

    if (troughs.size() < 3 || peaks.size() < 2) return false;

    // --- scan consecutive trough triples ---
    for (size_t k = 0; k + 2 < troughs.size(); ++k) {

        int left  = troughs[k];
        int head  = troughs[k + 1];
        int right = troughs[k + 2];

        double L = price[left];
        double H = price[head];
        double R = price[right];

        // --- Head must be LOWER than shoulders ---
        if (!(H < L && H < R)) continue;

        if (L / H < headRatioBefore) continue;
        if (R / H < headRatioAfter)  continue;

        // --- find two peaks between troughs (neckline) ---
        int p1 = -1, p2 = -1;

        for (int p : peaks) {
            if (p > left && p < head && p1 == -1) p1 = p;
            if (p > head && p < right && p2 == -1) p2 = p;
        }

        if (p1 == -1 || p2 == -1) continue;

        // --- neckline slope must be flat ---
        double sl = std::abs(slope(p1, price[p1], p2, price[p2]));
        if (sl > maxNeckSlope) continue;

        // --- ordering sanity ---
        if (!(left < p1 && p1 < head && head < p2 && p2 < right))
            continue;

        return true;
    }

    return false;
}


PatternResult InverseHeadShoulderDetector::detect(const std::vector<double>& price) {

    bool found = findInverseHeadShoulder(price);

    PatternResult result;
    result.pattern = PATTERN :: INVERSE_HEAD_AND_SHOULDER;

    if (found)
        result.trend = TREND :: BULLISH;
    else
        result.trend = TREND :: NEUTRAL;

    return result;
}
