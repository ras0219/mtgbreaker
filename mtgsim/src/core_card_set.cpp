#include "core_card_set.hpp"
#include "utility.hpp"
#include "game.hpp"
#include "player.hpp"

const CardInfo CardMixin<ChargingBadger>::info_data = {
    "chargingbadger",
    "Charging Badger",
    { "green", "creature", "badger", "trample" },
    1,
    ManaPool(std::array<unsigned int, 6>{{0, 1, 0, 0, 0, 0}}),
    1,
    1
};

const CardInfo CardMixin<WalkingCorpse>::info_data = {
    "walkingcorpse",
    "Walking Corpse",
    { "black", "creature", "zombie" },
    2,
    ManaPool(std::array<unsigned int, 6>{{1, 0, 1, 0, 0, 0}}),
    2,
    2
};

const CardInfo CardMixin<TyphoidRats>::info_data = {
    "typhoidrats",
    "Typhoid Rats",
    { "black", "creature", "rat", "deathtouch" },
    1,
    ManaPool(std::array<unsigned int, 6>{{0, 0, 1, 0, 0, 0}}),
    1,
    1
};

const CardInfo CardMixin<AlloyMyr>::info_data = {
    "alloymyr",
    "Alloy Myr",
    { "colorless", "artifact", "creature", "myr" },
    3,
    ManaPool(std::array<unsigned int, 6>{{3, 0, 0, 0, 0, 0}}),
    2,
    2
};

void AlloyMyr::tap_for_mana(Game* g, Player* p, ManaPool::Type t) {
    auto msg = check_tap(g, p);
    if (msg)
        throw std::runtime_error(msg);
    if (sick)
        throw std::runtime_error("Cannot tap creatures with summoning sickness");

    tapped = true;
    p->mana += t;
}


/// Lands
const CardInfo CardMixin<Forest>::info_data = {
    "forest",
    "Forest",
    { "colorless", "land", "basicland" },
    0,
    SMP<>(),
    0,
    0
};

const CardInfo CardMixin<Swamp>::info_data = {
    "swamp",
    "Swamp",
    { "colorless", "land", "basicland" },
    0,
    SMP<>(),
    0,
    0
};

const CardInfo CardMixin<Mountain>::info_data = {
    "mountain",
    "Mountain",
    { "colorless", "land", "basicland" },
    0,
    SMP<>(),
    0,
    0
};

const CardInfo CardMixin<Island>::info_data = {
    "island",
    "Island",
    { "colorless", "land", "basicland" },
    0,
    SMP<>(),
    0,
    0
};

const CardInfo CardMixin<Plains>::info_data = {
    "plains",
    "Plains",
    { "colorless", "land", "basicland" },
    0,
    SMP<>(),
    0,
    0
};

