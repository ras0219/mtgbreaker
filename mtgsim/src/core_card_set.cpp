#include "core_card_set.hpp"
#include "utility.hpp"
#include "game.hpp"
#include "player.hpp"

const CardInfo CardMixin<ChargingBadger>::info_data = {
    "chargingbadger",
    "Charging Badger",
    { "green", "creature", "badger", "trample" },
    1,
    SMP<ManaPool::GREEN>(),
    1,
    1
};

const CardInfo CardMixin<WalkingCorpse>::info_data = {
    "walkingcorpse",
    "Walking Corpse",
    { "black", "creature", "zombie" },
    2,
    SMP<ManaPool::BLACK, ManaPool::COLORLESS>(),
    2,
    2
};

const CardInfo CardMixin<TyphoidRats>::info_data = {
    "typhoidrats",
    "Typhoid Rats",
    { "black", "creature", "rat", "deathtouch" },
    1,
    SMP<ManaPool::BLACK>(),
    1,
    1
};

const CardInfo CardMixin<AlloyMyr>::info_data = {
    "alloymyr",
    "Alloy Myr",
    { "colorless", "artifact", "creature", "myr" },
    3,
    SMP<ManaPool::COLORLESS, ManaPool::COLORLESS, ManaPool::COLORLESS>(),
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

const CardInfo CardMixin<LightningBolt>::info_data = {
    "lightningbolt",
    "Lightning Bolt",
    { "red", "instant" },
    1,
    SMP<ManaPool::RED>(),
    0,
    0
};

void LightningBolt::enact(Game* g, Player* p, Player* target) {
    target->apply_damage(g, 3);
}

void LightningBolt::enact(Game* g, Player* p, Card* target) {
    if (!target->info().has("creature"))
        throw std::runtime_error("Target is not a creature");
    if (g->battlefield.end() == g->find_in_battlefield(target))
        throw std::runtime_error("Target is not in play");
    target->apply_damage(g, 3);
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

