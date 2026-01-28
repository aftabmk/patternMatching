#include "doublepattern.hpp"
#include <cmath>
#include <algorithm>

bool DoublePatternDetector::isLocalMax(const std::vector<double>& p, int i) {
    return p[i] > p[i-1] && p[i] > p[i+1];
}

bool DoublePatternDetector::isLocalMin(const std::vector<double>& p, int i) {
    return p[i] < p[i-1] && p[i] < p[i+1];
}


//-------------------------------------------
// Extract last 5 pivot values
//-------------------------------------------
static bool extractLast5Pivots(const std::vector<double>& price,std::vector<double>& pivots) {
    std::vector<double> tmp;

    for (int i = 1; i < (int)price.size() - 1; ++i) {
        if (price[i] > price[i-1] && price[i] > price[i+1])
            tmp.push_back(price[i]);
        else if (price[i] < price[i-1] && price[i] < price[i+1])
            tmp.push_back(price[i]);
    }

    if (tmp.size() < 5) return false;

    pivots.assign(tmp.end() - 5, tmp.end());
    return true;
}


//-------------------------------------------
// Double Top
//-------------------------------------------
bool DoublePatternDetector::detectDoubleTop(const std::vector<double>& price,double maxRatio) {
    std::vector<double> p;
    if (!extractLast5Pivots(price, p)) return false;

    // Python equivalent conditions
    if (p[0] < p[1] && p[0] < p[3] &&
        p[2] < p[1] && p[2] < p[3] &&
        p[4] < p[1] && p[4] < p[3] &&
        p[1] > p[3] &&
        (p[1] / p[3]) <= maxRatio)
        return true;

    return false;
}


//-------------------------------------------
// Double Bottom
//-------------------------------------------
bool DoublePatternDetector::detectDoubleBottom(const std::vector<double>& price,double minRatio) {
    std::vector<double> p;
    if (!extractLast5Pivots(price, p)) return false;

    if (p[0] > p[1] && p[0] > p[3] &&
        p[2] > p[1] && p[2] > p[3] &&
        p[4] > p[1] && p[4] > p[3] &&
        p[1] < p[3] &&
        (p[1] / p[3]) >= minRatio)
        return true;

    return false;
}


//-------------------------------------------
// Public Detect
//-------------------------------------------
PatternResult DoublePatternDetector::detect(const std::vector<double>& price) {

    bool top    = detectDoubleTop(price),  bottom = detectDoubleBottom(price);

    PatternResult result;
	
    if (top) {
		result.pattern = PATTERN :: DOUBLE_TOP;
        result.trend = TREND :: BEARISH ;
    }
    else if (bottom) {
		result.pattern = PATTERN :: DOUBLE_BOTTOM;
        result.trend = TREND :: BULLISH;
    }
    else {
		result.pattern = PATTERN :: DOUBLE_PATTERN;
        result.trend = TREND :: NEUTRAL;
    }

    return result;
}
