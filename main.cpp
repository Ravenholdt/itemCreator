
#include <cstdio>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <type_traits>
#include <vector>

#include "spell.h"
#include "effect.h"
#include "staff.h"

#define LEVEL_CHARACTER 7
#define LEVEL_MYTHIC 2

#define CASTERLEVEL_MAX LEVEL_CHARACTER

itemValueS itemValueMax[11] = 
{
    1, 2000,
    2, 8000,
    3, 18000,
    4, 32000,
    6, 72000,
    7, 98000,
    9, 162000,
    10, 200000,
    12, 288000,
    13, 338000,
    15, 450000,
};

struct itemS
{
    int level;
    std::vector<effectS> effects;
    staffS staff;
};

int calculateValue(itemS item)
{
    itemValueS itemValue = {0, 0};
    for(const effectS& effect : item.effects) 
    {
        itemValue.bonus += effect.value.bonus;
        itemValue.gold += effect.value.gold;
        std::cout << "Adding " << effect.name << " to item. (" << effect.value.gold << ")" << std::endl;
    }

    if (itemValue.bonus > itemValueMax->bonus &&
        itemValue.gold > itemValueMax->gold)
    {
        return -1;
    }

    std::cout << "Item price: " << itemValue.gold << std::endl;
    std::cout << "Value left: " << itemValueMax[item.level].gold - itemValue.gold << std::endl;
    return itemValue.gold;
}

effectS spellTrigger(spellS spell, int casterLevel, bool continious = false, int charges = 5)
{
    float levelMod = spell.spellLevel == 0 ? 0.5 : spell.spellLevel;
    if (casterLevel == 0) casterLevel = spell.spellLevel * 2 - 1;
    if (casterLevel < 1) casterLevel = 1; // Caster level should never be below 1.

    std::cout << "Caster level: " << casterLevel << std::endl;
    std::cout << "Spell level mod: " << levelMod << std::endl;
    
    effectS effect;
    effect.name = spell.name;
    if (continious) { effect.name.append(", Continious"); }
    effect.value.gold = (levelMod * casterLevel * 2000) * (5 / charges) * (continious ? spell.duration : 1);
    return effect;
}

void test(std::string spell)
{
    std::cout << "TEST" << std::endl;
    int value = spellTrigger(spellList[spell], CASTERLEVEL_MIN, false).value.gold;
    std::cout << "Test value: " << value << std::endl;
    std::cout << "END TEST" << std::endl << "---------------------------" << std::endl;
}

int main()
{
    std::cout << "Spells in spell list: " << populateSpellList() << std::endl << std::endl;
    test("Detect Magic");

    itemS staffOfMorric = {LEVEL_MYTHIC};

    staffOfMorric.effects.push_back({"Lesser Maximize", {0, 14000}});
    staffOfMorric.effects.push_back(spellTrigger(spellList["Shield"], CASTERLEVEL_MIN, true));

    staffOfMorric.staff.spells.push_back(staffSpell("Shield", 1));
    staffOfMorric.staff.spells.push_back(staffSpell("Arcane Sight", 1));
    staffOfMorric.staff.spells.push_back(staffSpell("Teleport", 1));

    int value = calculateValue(staffOfMorric);
    if (value >= 0)
    {
        printf("Valid Item!\n");
    } else {
        printf("Invalid item\n");
    }
}