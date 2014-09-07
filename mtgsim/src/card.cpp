#include "card.hpp"
#include "game.hpp"
#include "utility.hpp"

const char* Card::check_tap(Game* g, Player* p) {
    auto& bf = g->battlefield;

    // Does the player control it?
    CHECK_RETURN(controller != p);
    // Is it in play?
    CHECK_RETURN(std::find(bf.begin(), bf.end(), this) != bf.end());
    // Is it not tapped?
    CHECK_RETURN(!tapped);

    return nullptr;
}

void Card::apply_damage(Game* g, int dmg) {
    damage += dmg;
    if (damage >= info().toughness)
        g->pending_death.push_back(this);
}
