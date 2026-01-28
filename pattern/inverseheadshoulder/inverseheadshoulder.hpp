#pragma once
#include <vector>

#include "../utils/filter.hpp"

#include "../../namespace/trend.hpp"
#include "../../namespace/pattern.hpp"

#include "../../type/patternresult.hpp"

class InverseHeadShoulderDetector {
public:
    static PatternResult detect(const std::vector<double>& price);

private:
    static bool isLocalMin(const std::vector<double>& price, int i);
    static bool findPattern(const std::vector<double>& price);
};
