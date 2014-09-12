#pragma once

#include <vector>
#include <string>

#include "mana.hpp"

struct CardInfo
{
    std::string id;
    std::string name;
    std::vector<std::string> texts;
    std::vector<std::string> abilities;

    /// converted mana cost
    unsigned int cmc;
    /// mana cost
    ManaPool cost;

    unsigned int power;
    unsigned int toughness;

    bool has_text(const char* text) const {
        return std::find(texts.begin(), texts.end(), text) != texts.end();
    }
    bool has_ability(const char* ab) const {
        return std::find(abilities.begin(), abilities.end(), ab) != abilities.end();
    }
};