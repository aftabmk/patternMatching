#pragma once

#include <cmath>
#include <vector>
#include <iostream>

#include "../../namespace/trend.hpp"
#include "../../namespace/pattern.hpp"

#include "../../type/patternresult.hpp"

#include "../utils/filter.hpp"
class DoubleBottomDetector {
    static bool isLocalMin(const std::vector<double>& price, int index);
    static bool findDoubleBottom(const std::vector<double>& price);
public:
    static PatternResult detect(const std::vector<double>& price);
};
