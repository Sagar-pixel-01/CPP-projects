#pragma once
#include <cstdint>

enum class Side : int {
    BUY = 0,
    Sell = 1
};

struct  Trade
{
    /* data */
    int64_t buyOrdId;
    int64_t sellOrdId;
    int32_t instrId;
    int64_t price;
    int64_t qty;
};
