#pragma once

#include <algorithm>
#include <ostream>
#include <vector>
#include <iostream>

#include "effect.h"
#include "spell.h"

struct staffS
{
    int value = 0;
    int casterLevel = 8;
    std::vector<spellS> spells = {};

    int calculateValue();
    void staffSpell(std::string name, int charges = 1);
};

inline void staffS::staffSpell(std::string name, int charges)
{
    spellS spell = spellList[name];
    spell.charges = charges;
    spells.push_back(spell);
}

inline int staffS::calculateValue()
{
    if (spells.empty()) { return 0; }
    std::sort(spells.begin(), spells.end(), sortSpells);

    int spellCasterLevel = spells[0].spellLevel * 2 - 1;
    if (casterLevel < spellCasterLevel) { casterLevel = spellCasterLevel; }

    int i = 0;
    for (const spellS& spell : spells) 
    {
        int priceMod = 800;
        switch (i) {
            case 0:
                priceMod = priceMod;
                break;
            case 1:
                priceMod = priceMod * 0.75;
                break;
            default:
                priceMod = priceMod * 0.50;
        }

        int spellValue = (spell.spellLevel * casterLevel * priceMod) / spell.charges + (spell.castingCost * 50);
        std::cout << "Staff-print: " << spells[i].name 
                  << ", CL: " << casterLevel 
                  << ", Charges: " << spells[i].charges
                  << ", (" << spellValue  
                  << ", " << priceMod << ")" << std::endl;
        value += spellValue;
        i++;
    }
    std::cout << "Staff value: " << value << std::endl;
    return value;
}
