#pragma once

#include "card.hpp"
#include "creature.hpp"
#include "land.hpp"

struct Forest : LandMixinEx<Forest>
{
    static const CardInfo info_data;
};

const CardInfo Forest::info_data = {
    "forest",
    "Forest",
    { "green", "land", "basic land" },
    0,
    SMP<>(),
    0,
    0
};

struct ChargingBadger : CreatureMixinEx<ChargingBadger>
{
    static const CardInfo info_data;
};

const CardInfo ChargingBadger::info_data = {
    "chargingbadger",
    "Charging Badger",
    { "green", "creature", "badger", "trample" },
    1,
    SMP<ManaPool::GREEN>(),
    1,
    1
};
