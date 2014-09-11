#pragma once

#include <vector>
#include <string>

#include "mana.hpp"

struct CardInfo
{
    std::string id;
    std::string name;
    std::vector<std::string> attrs;

    /// converted mana cost
    unsigned int cmc;
    /// mana cost
    ManaPool cost;

    unsigned int power;
    unsigned int toughness;

    bool has(const char* attr) const {
        return std::find(attrs.begin(), attrs.end(), attr) != attrs.end();
    }
};