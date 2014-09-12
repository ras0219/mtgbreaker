#pragma once

#include "card.hpp"
#include "creature.hpp"
#include "land.hpp"
#include "spell.hpp"

struct Forest : LandMixinEx<Forest> {};
struct Swamp : LandMixinEx<Swamp> {};
struct Mountain : LandMixinEx<Mountain> {};
struct Island : LandMixinEx<Island> {};
struct Plains : LandMixinEx<Plains> {};

struct ChargingBadger : CreatureMixinEx<ChargingBadger> {};
struct WalkingCorpse : CreatureMixinEx<WalkingCorpse> {};
struct TyphoidRats : CreatureMixinEx<TyphoidRats> {};

struct AlloyMyr : CreatureMixinEx<AlloyMyr> {
    void tap_for_mana(Game* g, Player* p, ManaPool::Type t);
};

/////////////////////////////////////

struct GiantGrowth : SpellMixinEx<GiantGrowth> {
    void enact(Game* g, Player* p, Card* tgt);
};