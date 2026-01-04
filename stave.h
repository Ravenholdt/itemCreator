#pragma once

#include <algorithm>
#include <vector>

#include "spell.h"

struct staveS
{
    int value = 0;
    int casterLevel = 8;
    std::vector<spellS> spells;
};

inline int staveCalculateValue(staveS *stave)
{
    std::sort(stave->spells.begin(), stave->spells.end(), sortSpells);

    int casterLevel = stave->spells[0].spellLevel * 2 - 1;
    stave->casterLevel = stave->casterLevel < casterLevel ? casterLevel : 8;

    int priceMod = 800;
    for (int i = 0 ; i < stave->spells.size() ; i++)
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

        stave->value += stave->spells[i].spellLevel * casterLevel * priceMod;
    }

    return 0;
}
