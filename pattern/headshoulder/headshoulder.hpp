#pragma once
#include <vector>

#include "../../type/PatternResult.hpp"

#include "../../namespace/trend.hpp"
#include "../../namespace/pattern.hpp"

#include "../utils/filter.hpp"

class HeadShoulderDetector {
public:
    static PatternResult detect(const std::vector<double>& price);

private:
    static bool isLocalMax(const std::vector<double>& price, int i);
    static bool findPattern(const std::vector<double>& price);
};
