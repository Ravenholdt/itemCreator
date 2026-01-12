#pragma once

#include <string>

struct itemValueS
{
    int bonus = 0;
    int gold = 0;
};

struct effectS
{
    std::string name;
    itemValueS value;
};