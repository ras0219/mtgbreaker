#include "card.hpp"
#include <algorithm>

bool Card::has_text(const char* text) const {
    return std::find(texts.begin(), texts.end(), text) != texts.end();
}
bool Card::has_ability(const char* ab) const {
    return std::find(abilities.begin(), abilities.end(), ab) != abilities.end();
}
