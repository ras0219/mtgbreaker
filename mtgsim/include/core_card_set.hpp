#pragma once

#include "card.hpp"
#include "creature.hpp"
#include "land.hpp"

struct Forest : LandMixinEx<Forest> {};

struct Swamp : LandMixinEx<Swamp> {};

struct ChargingBadger : CreatureMixinEx<ChargingBadger> {};

struct WalkingCorpse : CreatureMixinEx<WalkingCorpse> {};

struct TyphoidRats : CreatureMixinEx<TyphoidRats> {};
