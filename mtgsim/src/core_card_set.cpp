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

const CardInfo CardMixin<Forest>::info_data = {
    "forest",
    "Forest",
    { "green", "land", "basic land" },
    0,
    SMP<>(),
    0,
    0
};
