#include "core_card_set.hpp"

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
