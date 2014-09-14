#pragma once

#include "card.hpp"
#include "creature.hpp"
#include "land.hpp"
#include "spell.hpp"
#include <memory>

struct Forest : BasicLandMixin<ManaPool::GREEN, Forest> {};
struct Swamp : BasicLandMixin<ManaPool::BLACK, Swamp> {};
struct Mountain : BasicLandMixin<ManaPool::RED, Mountain> {};
struct Island : BasicLandMixin<ManaPool::BLUE, Island> {};
struct Plains : BasicLandMixin<ManaPool::WHITE, Plains> {};

struct ChargingBadger : CreatureMixin<ChargingBadger> {};
#if 0
struct WalkingCorpse : CreatureMixin<WalkingCorpse> {};
struct TyphoidRats : CreatureMixin<TyphoidRats> {};
struct BorderlandMarauder : CreatureMixin<BorderlandMarauder> {
    BorderlandMarauder();
    ~BorderlandMarauder();

private:
    friend struct BorderlandMarauderModifier;
    std::unique_ptr<BorderlandMarauderModifier> mod;
};

struct AlloyMyr : CreatureMixin<AlloyMyr> {
    void tap_for_mana(Game* g, Player* p, ManaPool::Type t);
};

/////////////////////////////////////
#endif

struct GiantGrowth : SpellMixin<GiantGrowth> {
    void enact(Game* g, Player* p, Permanent* tgt);
};
