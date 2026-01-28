#pragma once

#include <cmath>
#include <vector>
#include <iostream>

#include "../../namespace/trend.hpp"
#include "../../namespace/pattern.hpp"

#include "../../type/patternresult.hpp"

class DoubleTopDetector {
    static bool findDoubleTop(const std::vector<double>& price);
    static bool isLocalMax(const std::vector<double> &price,int i);
public:
    static PatternResult detect(const std::vector<double>& price);
};

