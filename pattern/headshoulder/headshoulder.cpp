#include "headshoulder.hpp"
#include <cmath>
#include <algorithm>

bool HeadShoulderDetector::isLocalMax(const std::vector<double>& p, int i) {
    return p[i] > p[i-1] && p[i] > p[i+1];
}

bool HeadShoulderDetector::isLocalMin(const std::vector<double>& p, int i) {
    return p[i] < p[i-1] && p[i] < p[i+1];
}


// simple slope between two points
static double slope(int x1, double y1, int x2, double y2) {
    return (y2 - y1) / (double)(x2 - x1);
}


bool HeadShoulderDetector::findHeadShoulder(
    const std::vector<double>& price,
    double headRatioBefore,
    double headRatioAfter,
    double maxNeckSlope
) {
    const int n = price.size();
    if (n < 10) return false;

    std::vector<int> peaks;
    std::vector<int> valleys;

    // --- find local peaks and valleys ---
    for (int i = 1; i < n - 1; ++i) {
        if (isLocalMax(price, i)) peaks.push_back(i);
        if (isLocalMin(price, i)) valleys.push_back(i);
    }

    if (peaks.size() < 3 || valleys.size() < 2) return false;

    // --- scan consecutive peak triples ---
    for (size_t k = 0; k + 2 < peaks.size(); ++k) {

        int left  = peaks[k];
        int head  = peaks[k + 1];
        int right = peaks[k + 2];

        double L = price[left];
        double H = price[head];
        double R = price[right];

        // --- Head must be higher than shoulders ---
        if (!(H > L && H > R)) continue;

        if (H / L < headRatioBefore) continue;
        if (H / R < headRatioAfter)  continue;

        // --- find two valleys between peaks ---
        int v1 = -1, v2 = -1;

        for (int v : valleys) {
            if (v > left && v < head && v1 == -1) v1 = v;
            if (v > head && v < right && v2 == -1) v2 = v;
        }

        if (v1 == -1 || v2 == -1) continue;

        // --- neckline slope must be flat ---
        double sl = std::abs(slope(v1, price[v1], v2, price[v2]));
        if (sl > maxNeckSlope) continue;

        // --- ordering sanity ---
        if (!(left < v1 && v1 < head && head < v2 && v2 < right))
            continue;

        return true;
    }

    return false;
}


PatternResult HeadShoulderDetector::detect(const std::vector<double>& price) {

    bool found = findHeadShoulder(price);

    PatternResult result;
    result.pattern = PATTERN :: HEAD_AND_SHOULDER;

    if (found)
        result.trend = TREND :: BEARISH;
    else
        result.trend = TREND :: NEUTRAL;

    return result;
}
