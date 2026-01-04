#pragma once

#include <string>

struct itemValueS
{
    int bonus;
    int gold;
};

struct effectS
{
    std::string name;
    itemValueS value;
};