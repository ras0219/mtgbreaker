#include "burn_set.hpp"
#include "card_info.hpp"
#include "player.hpp"

// Lightning Bolt
const CardInfo CardMixin<LightningBolt>::info_data = {
    "lightningbolt",
    "Lightning Bolt",
    { "red", "instant" },
    {},
    1,
    ManaPool(std::array<unsigned int, 6>{{0, 0, 0, 0, 0, 1}}),
    0,
    0
};

// Volcanic Hammer
const CardInfo CardMixin<VolcanicHammer>::info_data = {
    "volcanichammer",
    "Volcanic Hammer",
    { "red", "instant" },
    {},
    2,
    ManaPool(std::array<unsigned int, 6>{{1, 0, 0, 0, 0, 1}}),
    0,
    0
};

// Shock
const CardInfo CardMixin<Shock>::info_data = {
    "shock",
    "Shock",
    { "red", "instant" },
    {},
    1,
    ManaPool(std::array<unsigned int, 6>{{0, 0, 0, 0, 0, 1}}),
    0,
    0
};

// Lava Axe
const CardInfo CardMixin<LavaAxe>::info_data = {
    "lavaaxe",
    "Lava Axe",
    { "red", "sorcery" },
    {},
    5,
    ManaPool(std::array<unsigned int, 6>{{4, 0, 0, 0, 0, 1}}),
    0,
    0
};

void LavaAxe::enact(Game* g, Player* p, Player* target) {
    target->apply_damage(g, this, 5);
}

// Lava Spike
const CardInfo CardMixin<LavaSpike>::info_data = {
    "lavaspike",
    "Lava Spike",
    { "red", "sorcery", "arcane" },
    {},
    1,
    ManaPool(std::array<unsigned int, 6>{{0, 0, 0, 0, 0, 1}}),
    0,
    0
};

void LavaSpike::enact(Game* g, Player* p, Player* target) {
    target->apply_damage(g, this, 3);
}

// Searing Blaze
const CardInfo CardMixin<SearingBlaze>::info_data = {
    "searingblaze",
    "Searing Blaze",
    { "red", "instant" },
    { "landfall" },
    2,
    ManaPool(std::array<unsigned int, 6>{{0, 0, 0, 0, 0, 2}}),
    0,
    0
};

void SearingBlaze::enact(Game* g, Player* p, Card* ct, Player* pt) {
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


// Anger of the Gods
const CardInfo CardMixin<AngerOfTheGods>::info_data = {
    "angerofthegods",
    "Anger of the Gods",
    { "red", "sorcery" },
    {},
    3,
    ManaPool(std::array<unsigned int, 6>{{1, 0, 0, 0, 0, 2}}),
    0,
    0
};

void AngerOfTheGods::enact(Game* g, Player* p) {
    for (auto c : g->battlefield) {
        if (c->has_text("creature")) {
            c->apply_damage(g, this, 3);
        }
    }
}

// Volcanic Fallout
const CardInfo CardMixin<VolcanicFallout>::info_data = {
    "volcanicfallout",
    "Volcanic Fallout",
    { "red", "instant" },
    {},
    3,
    ManaPool(std::array<unsigned int, 6>{{1, 0, 0, 0, 0, 2}}),
    0,
    0
};

void VolcanicFallout::enact(Game* g, Player* p) {
    g->p1->apply_damage(g, this, 2);
    g->p2->apply_damage(g, this, 2);

    for (auto c : g->battlefield) {
        if (c->has_text("creature")) {
            c->apply_damage(g, this, 2);
        }
    }
}