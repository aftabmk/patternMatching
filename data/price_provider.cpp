#include "price_provider.hpp"

std::vector<double> headShoulder {
    100, 105, 110,   // left shoulder
    103, 108, 115,   // head
    104, 109, 111,   // right shoulder
    105, 102,  98    // breakdown
};

std::vector<double> inverseHeadShoulder {
    100, 95, 90,   // left shoulder
    92,  85,  80,   // head
    93,  88,  90,   // right shoulder
    95, 100, 105    // breakout
};

std::vector<double> doubleTop {
    100, 105, 110,   // peak 1
    95, 
    108, 111,        // peak 2 (almost equal)
    94,90             // breakdown
};

std::vector<double> doubleBottom {
    120, 110,  90,   // bottom 1
    115,
    92,             // bottom 2 (almost equal)
    118,
    130             // breakout
};


std::vector<double> getPriceData() {
    return headShoulder;
}
