#include "card.hpp"
#include "card_info.hpp"
#include "game.hpp"
#include "utility.hpp"
#include "modifier.hpp"
#include "stackable.hpp"
#include "player.hpp"

const char* Card::can_tap(Game* g, Player* p) const {
    // Does the player control it?
    CHECK_RETURN(controller == p);
    // Is it not tapped?
    CHECK_RETURN(!tapped);
    // Is it in play?
    CHECK_RETURN(g->is_in_play(this));
    // If it's a creature, is it sick?
    CHECK_RETURN(!has_text("creature") || !sick || has_ability("haste"));

    return nullptr;
}

void Card::tap(Game*, Player*) {
    tapped = true;
}

void Card::trigger(Stackable* s) {
    controller->triggered_abilities.push_back(s);
}

const char* Card::can_attack(Game* g, Player* p) const {
    CHECK_RETURN(controller == p);
    CHECK_RETURN(!tapped);
    CHECK_RETURN(has_text("creature"));
    CHECK_RETURN(!sick || has_ability("haste"));
    return nullptr;
}

bool Card::has_text(const char* attr) const {
    for (auto m : m_l3) {
        auto t = m->has_text(attr);
        if (t == YES)
            return true;
        if (t == NO)
            return false;
    }
    return info().has_text(attr);
}

bool Card::has_ability(const char* attr) const {
    for (auto m : m_l6) {
        auto t = m->has_ability(attr);
        if (t == YES)
            return true;
        if (t == NO)
            return false;
    }
    return info().has_ability(attr);
}

int Card::power() const {
    int p = info().power;
    for (auto m : m_l7)
        p = m->power(p);
    return p;
}
int Card::toughness() const {
    int p = info().toughness;
    for (auto m : m_l7)
        p = m->toughness(p);
    return p;
}

void Card::apply_damage(Game* g, Card* src, int dmg) {
    damage += dmg;
    if (damage >= info().toughness)
        g->pending_death.push_back(this);
}
