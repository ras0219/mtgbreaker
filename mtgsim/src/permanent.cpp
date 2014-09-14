#include "card.hpp"
#include "game.hpp"
#include "utility.hpp"
#include "modifier.hpp"
#include "stackable.hpp"
#include "player.hpp"
#include "permanent.hpp"

const char* Permanent::can_tap(Game* g, Player* p) const {
    // Does the player control it?
    CHECK_RETURN(controller == p);
    // Is it not tapped?
    CHECK_RETURN(!tapped);
    // Is it in play?
    CHECK_RETURN(g->is_in_play(this));
    // If it's a creature, is it sick?
    CHECK_RETURN(!has_text("creature") || !sick);

    return nullptr;
}

void Permanent::tap(Game*, Player*) {
    tapped = true;
}

void Permanent::trigger(Stackable* s) {
    controller->triggered_abilities.push_back(s);
}

const char* Permanent::can_attack(Game* g, Player* p) const {
    CHECK_RETURN(controller == p);
    CHECK_RETURN(!tapped);
    CHECK_RETURN(has_text("creature"));
    CHECK_RETURN(!sick);
    return nullptr;
}

bool Permanent::has_text(const char* attr) const {
    for (auto m : m_l3) {
        auto t = m->has_text(attr);
        if (t == YES)
            return true;
        if (t == NO)
            return false;
    }
    return card->has_text(attr);
}

/*
bool Permanent::has_ability(const char* attr) const {
    for (auto m : m_l6) {
        auto t = m->has_ability(attr);
        if (t == YES)
            return true;
        if (t == NO)
            return false;
    }
    return card->has_ability(attr);
}
*/

int Permanent::power() const {
    int p = card->power;
    for (auto m : m_l7)
        p = m->power(p);
    return p;
}
int Permanent::toughness() const {
    int p = card->toughness;
    for (auto m : m_l7)
        p = m->toughness(p);
    return p;
}

void Permanent::apply_damage(Game* g, Permanent* src, int dmg) {
    damage += dmg;
    if ((int)damage >= toughness())
        g->pending_death.push_back(this);
}

void Permanent::apply_damage(Game* g, const Card* src, int dmg) {
    damage += dmg;
    if ((int)damage >= toughness())
        g->pending_death.push_back(this);
}
