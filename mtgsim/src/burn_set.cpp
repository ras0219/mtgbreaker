#include "burn_set.hpp"
#include "player.hpp"

#define BURN_CARDMIXIN_MACRO(TYPENAME, NAME, COLORLESS, RED, ...) \
CardMixin<TYPENAME>::CardMixin() {                 \
    name = NAME;                                         \
    texts = { "red", __VA_ARGS__ }; \
    cmc = RED + COLORLESS; \
    cost = ManaPool(std::array<unsigned int, 6>{{COLORLESS, 0, 0, 0, 0, RED}}); \
    power = 0; \
    toughness = 0; \
}

// Lightning Bolt
BURN_CARDMIXIN_MACRO(LightningBolt, "Lightning Bolt", 0, 1, "instant")
BURN_CARDMIXIN_MACRO(VolcanicHammer, "Volcanic Hammer", 1, 1, "instant")
BURN_CARDMIXIN_MACRO(Shock, "Shock", 0, 1, "instant")
BURN_CARDMIXIN_MACRO(LavaAxe, "Lava Axe", 4, 1, "sorcery")
BURN_CARDMIXIN_MACRO(LavaSpike, "Lava Spike", 0, 1, "sorcery", "arcane")
BURN_CARDMIXIN_MACRO(SearingBlaze, "Searing Blaze", 0, 2, "instant")
BURN_CARDMIXIN_MACRO(AngerOfTheGods, "Anger of the Gods", 1, 2, "sorcery")
BURN_CARDMIXIN_MACRO(VolcanicFallout, "Volcanic Fallout", 1, 2, "instant")

void LavaAxe::enact(Game* g, Player* p, Player* target) const {
    target->apply_damage(g, this, 5);
}

void LavaSpike::enact(Game* g, Player* p, Player* target) const {
    target->apply_damage(g, this, 3);
}

void SearingBlaze::enact(Game* g, Player* p, Permanent* ct, Player* pt) const {
    if (g->active_player == p && g->lands_played == 1) {
        // Landfall effect
        ct->apply_damage(g, this, 3);
        pt->apply_damage(g, this, 3);
    } else {
        // Normal effect
        ct->apply_damage(g, this, 1);
        pt->apply_damage(g, this, 1);
    }
}

void AngerOfTheGods::enact(Game* g, Player* p) const {
    for (auto c : g->battlefield) {
        if (c->has_text("creature")) {
            c->apply_damage(g, this, 3);
        }
    }
}

void VolcanicFallout::enact(Game* g, Player* p) const {
    g->p1->apply_damage(g, this, 2);
    g->p2->apply_damage(g, this, 2);

    for (auto c : g->battlefield) {
        if (c->has_text("creature")) {
            c->apply_damage(g, this, 2);
        }
    }
}