#include "card.hpp"
#include "card_info.hpp"
#include "game.hpp"
#include "utility.hpp"

const char* can_tap(Game* g, Player* p, Card* c) {
    auto& bf = g->battlefield;

    // Does the player control it?
    CHECK_RETURN(c->controller == p);
    // Is it not tapped?
    CHECK_RETURN(!c->tapped);
    // Is it in play?
    CHECK_RETURN(std::find(bf.begin(), bf.end(), c) != bf.end());
    // If it's a creature, is it sick?
    CHECK_RETURN(!c->info().has("creature") || !c->sick);

    return nullptr;
}

bool Card::has(const char* attr) const {
    return info().has(attr);
}

void Card::apply_damage(Game* g, int dmg) {
    damage += dmg;
    if (damage >= info().toughness)
        g->pending_death.push_back(this);
}
