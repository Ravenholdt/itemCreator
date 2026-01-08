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

#define CHARGES_UNLIMITED 0

struct spellS
{
    std::string name;
    int spellLevel;
    float duration;
    int castingCost;
    int charges = 0;
};

static std::map<std::string, spellS> spellList;

inline bool sortSpells(spellS a, spellS b)
{
    if (a.spellLevel != b.spellLevel) { return a.spellLevel > b.spellLevel; }
    return a.charges <= b.charges;
}

inline int populateSpellList()
{
    // 0
    spellList["Detect Magic"] = {"Detect Magic", 0, DURATION_minute_one, 0};
    spellList["Detect Poison"] = {"Detect Poison", 0, DURATION_NONE, 0};

    // 1
    spellList["Magic Missile"] = {"Magic Missile", 1, DURATION_NONE, 0};
    spellList["Protection from Evil"] = {"Protection from Evil", 1, DURATION_minute_one, 0};
    spellList["Shield"] = {"Shield", 1, DURATION_minute_one, 0};
    spellList["Snowball"] = {"Snowball", 1, DURATION_NONE, 0};

    // 2
    spellList["Protection from Evil, Communal"] = {"Protection from Evil, Communal", 2, DURATION_minute_one, 0};

    // 3
    spellList["Arcane Sight"] = {"Arcane Sight", 3, DURATION_minute_one, 0};
    spellList["Dispel Magic"] = {"Dispel Magic", 3, DURATION_NONE, 0};
    

    // 4
    spellList["Protection from Energy, Communal"] = {"Protection from Energy, Communal", 4, DURATION_minute_ten, 0};
    spellList["Scrying"] = {"Scrying", 4, DURATION_minute_one, 0};

    // 5
    spellList["Teleport"] = {"Teleport", 5, DURATION_NONE, 0};

    return spellList.size();
}