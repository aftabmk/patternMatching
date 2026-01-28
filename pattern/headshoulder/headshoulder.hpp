#pragma once
#include <vector>

#include "../../type/PatternResult.hpp"

#include "../../namespace/trend.hpp"
#include "../../namespace/ratio.hpp"
#include "../../namespace/pattern.hpp"


class HeadShoulderDetector {
public:
    static PatternResult detect(const std::vector<double>& price);

private:
    static bool isLocalMax(const std::vector<double>& p, int i);
    static bool isLocalMin(const std::vector<double>& p, int i);

    static bool findHeadShoulder(
        const std::vector<double>& price,
        double headRatioBefore = RATIO :: HEAD_AND_SHOULDER :: HEAD_RATIO_BEFORE,
        double headRatioAfter  = RATIO :: HEAD_AND_SHOULDER :: HEAD_RATIO_AFTER,
        double maxNeckSlope    = RATIO :: HEAD_AND_SHOULDER :: MAX_NECK_SLOPE
    );
};
