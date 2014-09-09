#include "burn_set.hpp"
#include "player.hpp"

// Lightning Bolt
const CardInfo CardMixin<LightningBolt>::info_data = {
    "lightningbolt",
    "Lightning Bolt",
    { "red", "instant" },
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
    1,
    ManaPool(std::array<unsigned int, 6>{{0, 0, 0, 0, 0, 1}}),
    0,
    0
};

// Lava Axe
const CardInfo CardMixin<LavaAxe>::info_data = {
    "lavaaxe",
    "Lava Axe",
    { "red", "instant" },
    5,
    ManaPool(std::array<unsigned int, 6>{{4, 0, 0, 0, 0, 1}}),
    0,
    0
};

void LavaAxe::enact(Game* g, Player* p, Player* target) {
    target->apply_damage(g, 5);
}
