#pragma once 
#include <cstdint>
#include "Types.h"


struct Order
{
    int64_t ordId;
    int64_t instrId;
    int64_t price;
    int64_t qty;
    int64_t triggerPrice = 0;
    bool isIoc = false;

    Side side = Side::BUY;
    int remaining = 0;

};
