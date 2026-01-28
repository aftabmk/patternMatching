#pragma once
#include <vector>

#include "../../type/patternresult.hpp"

#include "../../namespace/trend.hpp"
#include "../../namespace/ratio.hpp"
#include "../../namespace/pattern.hpp"

class DoublePatternDetector {
public:
    static PatternResult detect(const std::vector<double>& price);

private:
    static bool isLocalMax(const std::vector<double>& p, int i);
    static bool isLocalMin(const std::vector<double>& p, int i);

    static bool detectDoubleTop(
        const std::vector<double>& price,
        const double maxRatio = RATIO :: DOUBLE_PATTERN :: MAX_RATIO
    );

    static bool detectDoubleBottom(
        const std::vector<double>& price,
        const double minRatio = RATIO :: DOUBLE_PATTERN :: MIN_RATIO
    );
};
