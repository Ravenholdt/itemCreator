#pragma once

#include <map>
#include <string>

#define DURATION_round 4
#define DURATION_minute_one 2
#define DURATION_minute_ten 1.5
#define DURATION_hour 1
#define DURATION_day 0.5
#define DURATION_NONE 1

#define CASTERLEVEL_MIN 0

struct spellS
{
    std::string name;
    int spellLevel;
    float duration;
};

static std::map<std::string, spellS> spellList;

inline int populateSpellList()
{
    // 0
    spellList["Detect Magic"] = {"Detect Magic", 0, DURATION_minute_one};
    spellList["Detect Poison"] = {"Detect Poison", 0, DURATION_NONE};

    // 1
    spellList["Shield"] = {"Shield", 1, DURATION_minute_one};

    // 2
    // 3
    spellList["Arcane Sight"] = {"Arcane Sight", 3, DURATION_minute_one};

    // 4

    return spellList.size();
}