#include "filter.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>

double recentAverage(const std::vector<double>& price, int lookback) {
    int n = price.size();
    if (n < lookback) return price.back();

    double sum = 0.0;
    for (int i = n - lookback; i < n; ++i)
        sum += price[i];

    return sum / lookback;
}

bool nearRecentMax(const std::vector<double>& price, int lookback) {
    double avg = recentAverage(price, lookback);
    double maxP = *std::max_element(price.begin(), price.end());

    double diff = std::abs(avg - maxP) / std::max(1.0, std::abs(maxP));
    return diff < 0.02;   // within 2%
}

bool nearRecentMin(const std::vector<double>& price, int lookback) {
    double avg = recentAverage(price, lookback);
    double minP = *std::min_element(price.begin(), price.end());

    double diff = std::abs(avg - minP) / std::max(1.0, std::abs(minP));
    return diff < 0.02;   // within 2%
}
