#pragma once

#include "card.hpp"
#include "creature.hpp"
#include "land.hpp"
#include "spell.hpp"
#include <memory>

/////////////////////////////////////
// Lands

struct Forest : BasicLandMixin<ManaPool::GREEN, Forest> {};
struct Swamp : BasicLandMixin<ManaPool::BLACK, Swamp> {};
struct Mountain : BasicLandMixin<ManaPool::RED, Mountain> {};
struct Island : BasicLandMixin<ManaPool::BLUE, Island> {};
struct Plains : BasicLandMixin<ManaPool::WHITE, Plains> {};

/////////////////////////////////////
// Creatures

struct ChargingBadger : CreatureMixin<ChargingBadger> {};
struct WalkingCorpse : CreatureMixin<WalkingCorpse> {};
struct TyphoidRats : CreatureMixin<TyphoidRats> {};

struct BorderlandMarauder : CreatureMixinEx<BorderlandMarauder> {
    static void apply_base_modifiers(Game* g, Player* p, Permanent* m);
};
struct AlloyMyr : CreatureMixinEx<AlloyMyr> {
    static void apply_base_modifiers(Game* g, Player* p, Permanent* m);
};

/////////////////////////////////////
// Spells

struct GiantGrowth : SpellMixin<GiantGrowth> {
    void enact(Game* g, Player* p, Permanent* tgt);
};
