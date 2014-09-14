#pragma once

#include <stdexcept>
#include <string>
#include <vector>
#include "mana.hpp"

struct Card
{
    /// Read-only card information
public:
    std::string name;
    std::vector<std::string> texts;
    std::vector<std::string> abilities;

    /// converted mana cost
    unsigned int cmc;
    /// mana cost
    ManaPool cost;

    unsigned int power;
    unsigned int toughness;

    /// Utility functions
public:
    bool has_text(const char* text) const;
    bool has_ability(const char* ab) const;
};

template<class C>
const C* card_cast(const Card* c) {
    static_assert(std::is_base_of<Card, C>::value, "Cannot cast to non-card");
    if (c == &C::instance)
        return &C::instance;
    else
        throw std::runtime_error("bad card cast");
}
