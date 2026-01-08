
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

#define LEVEL_CHARACTER 8
#define LEVEL_MYTHIC 3

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
    std::vector<effectS> effects = {};
    staffS staff;

    int calculateValue();
    void spellTrigger(std::string spellName, int casterLevel, bool continious = false, int charges = CHARGES_UNLIMITED);
};

int itemS::calculateValue()
{
    itemValueS itemValue = {0, 0};
    for(const effectS& effect : effects) 
    {
        itemValue.bonus += effect.value.bonus;
        itemValue.gold += effect.value.gold;
        std::cout << "Adding " << effect.name << " to item. (" << effect.value.gold << ")" << std::endl;
    }

    itemValue.gold += staff.calculateValue();

    std::cout << "Item price: " << itemValue.gold << std::endl;
    std::cout << "Value left: " << itemValueMax[level].gold - itemValue.gold << std::endl;

    if (itemValue.bonus > itemValueMax->bonus &&
        itemValue.gold > itemValueMax->gold)
    {
        return -1;
    }
    return itemValue.gold;
}



void itemS::spellTrigger(std::string spellName, int casterLevel, bool continious, int charges)
{
    int componentCostModifier = charges == CHARGES_UNLIMITED ? 100 : 50;
    if (charges == CHARGES_UNLIMITED) { charges = 5; }
    spellS spell = spellList[spellName];
    float levelMod = spell.spellLevel == 0 ? 0.5 : spell.spellLevel;
    if (casterLevel == 0) casterLevel = spell.spellLevel * 2 - 1;
    if (casterLevel < 1) casterLevel = 1; // Caster level should never be below 1.

    std::cout << "Caster level: " << casterLevel << std::endl;
    std::cout << "Spell level mod: " << levelMod << std::endl;
    
    effectS effect;
    effect.name = spell.name;
    if (continious) { effect.name.append(", Continious"); }
    effect.value.gold = ((levelMod * casterLevel * 2000) / (5 / charges)) * (continious ? spell.duration : 1)
                         + (spell.castingCost *componentCostModifier);
    effects.push_back(effect);
}

void test(std::string spell)
{
    std::cout << "TEST" << std::endl;
    itemS item = {10};
    item.spellTrigger(spell, CASTERLEVEL_MIN, false);
    int value = item.calculateValue();
    std::cout << "Test value: " << value << std::endl;
    std::cout << "END TEST" << std::endl << "---------------------------" << std::endl;
}

void staffTest()
{
    std::cout << "TEST - STAFF" << std::endl;
    itemS item = {10};
    item.staff.staffSpell("Dispel Magic", 2);
    item.staff.staffSpell("Arcane Sight");

    int value = item.staff.calculateValue();

    std::cout << "Test value: " << value << std::endl;
    std::cout << "END TEST - STAFF" << std::endl << "---------------------------" << std::endl;
}

int main()
{
    std::cout << "Spells in spell list: " << populateSpellList() << std::endl << std::endl;
//    test("Dispel Magic");
//    staffTest();

    itemS staffOfMorric = {LEVEL_MYTHIC};

    staffOfMorric.effects.push_back({"Lesser Maximize", {0, 14000}});

    staffOfMorric.spellTrigger("Shield", CASTERLEVEL_MIN, true);
//    staffOfMorric.spellTrigger("Protection from Evil, Communal", CASTERLEVEL_MIN, false, 2);

    staffOfMorric.staff.staffSpell("Dispel Magic", 2);
//    staffOfMorric.staff.staffSpell("Scrying", 4);
//    staffOfMorric.staff.staffSpell("Protection from Evil, Communal", 1);
//    staffOfMorric.staff.staffSpell("Snowball", 1);

    int value = staffOfMorric.calculateValue();
    if (value >= 0)
    {
        printf("Valid Item!\n");
    } else {
        printf("Invalid item\n");
    }
}