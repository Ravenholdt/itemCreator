#pragma once

#include <algorithm>
#include <vector>

#include "effect.h"
#include "spell.h"

struct staffS
{
    int value = 0;
    int casterLevel = 8;
    std::vector<spellS> spells;
};

inline spellS staffSpell(std::string name, int charges)
{
    return spellList[name];
}

inline int staveCalculateValue(staffS *staff)
{
    std::sort(staff->spells.begin(), staff->spells.end(), sortSpells);

    int casterLevel = staff->spells[0].spellLevel * 2 - 1;
    staff->casterLevel = staff->casterLevel < casterLevel ? casterLevel : 8;

    int priceMod = 800;
    for (int i = 0 ; i < staff->spells.size() ; i++)
    {
        switch (i) {
            case 0:
                priceMod = priceMod;
                continue;
            case 1:
                priceMod = priceMod * 0.75;
                continue;
            default:
                priceMod = priceMod * 0.50;
        }

        staff->value += staff->spells[i].spellLevel * casterLevel * priceMod;
    }

    return 0;
}
