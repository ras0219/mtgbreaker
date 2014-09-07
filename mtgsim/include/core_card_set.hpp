#pragma once

#include "card.hpp"
#include "creature.hpp"
#include "land.hpp"

struct Forest : LandMixinEx<Forest> {};
struct Swamp : LandMixinEx<Swamp> {};
struct Mountain : LandMixinEx<Mountain> {};
struct Island : LandMixinEx<Island> {};
struct Plains : LandMixinEx<Plains> {};

struct ChargingBadger : CreatureMixinEx<ChargingBadger> {};

struct WalkingCorpse : CreatureMixinEx<WalkingCorpse> {};

struct TyphoidRats : CreatureMixinEx<TyphoidRats> {};
