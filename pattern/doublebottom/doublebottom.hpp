#pragma once

#include <cmath>
#include <vector>
#include <iostream>

#include "../../namespace/trend.hpp"
#include "../../namespace/pattern.hpp"

#include "../../type/patternresult.hpp"

class DoubleBottomDetector {
public:
    static PatternResult detect(const std::vector<double>& price);

private:
    static bool isLocalMin(const std::vector<double>& price, int i);
    static bool findDoubleBottom(const std::vector<double>& price);
};
