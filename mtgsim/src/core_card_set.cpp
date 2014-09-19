#include "core_card_set.hpp"
#include "utility.hpp"
#include "game.hpp"
#include "player.hpp"
#include "modifier.hpp"
#include "modifier_mixin.hpp"
#include <map>

CardMixin<ChargingBadger>::CardMixin() {
    name = "Charging Badger";
    texts = { "green", "creature", "badger" };
    abilities = { "trample" };
    cmc = 1;
    cost = ManaPool(std::array < unsigned int, 6 > {{0, 1, 0, 0, 0, 0}});
    power = 1;
    toughness = 1;
};

CardMixin<WalkingCorpse>::CardMixin() {
    name = "Walking Corpse";
    texts = { "black", "creature", "zombie" };
    cmc = 2;
    cost = ManaPool(std::array < unsigned int, 6 > {{1, 0, 1, 0, 0, 0}});
    power = 2;
    toughness = 2;
};

CardMixin<TyphoidRats>::CardMixin() {
    name = "Typhoid Rats";
    texts = { "black", "creature", "rat" };
    abilities = { "deathtouch" };
    cmc = 1;
    cost = ManaPool(std::array < unsigned int, 6 > {{0, 0, 1, 0, 0, 0}});
    power = 1;
    toughness = 1;
};

CardMixin<BorderlandMarauder>::CardMixin() {
    name = "Borderland Marauder";
    texts = { "red", "creature", "human", "warrior" };
    cmc = 2;
    cost = ManaPool(std::array < unsigned int, 6 > {{1, 0, 0, 1, 0, 0}});
    power = 1;
    toughness = 2;
};

struct BorderlandMarauderBuff : TillEndOfTurnL7Mixin<BorderlandMarauderBuff> {
    BorderlandMarauderBuff(Game* g) : TillEndOfTurnL7Mixin<BorderlandMarauderBuff>(g) {}

    int power(int prev) const { return prev + 2; }
    int toughness(int prev) const { return prev; }
};

struct BorderlandMarauderBuffStackable : Stackable {
    BorderlandMarauderBuffStackable(Permanent* bm) : c(bm) {}

    void resolve(Game* g) {
        BorderlandMarauderBuff::instance(g)->attach(c);
    }

    Permanent* c;
};

struct BorderlandMarauderModifier : Modifier {
    void when_attacks(Game*, Permanent* c) {
        c->trigger(new BorderlandMarauderBuffStackable{c});
    }

    static BorderlandMarauderModifier instance;
};
BorderlandMarauderModifier BorderlandMarauderModifier::instance;

void BorderlandMarauder::apply_base_modifiers(Game* g, Player* p, Permanent* m) {
    m->add<Modifier>(&BorderlandMarauderModifier::instance);
}

/////////////////////////////////////
CardMixin<AlloyMyr>::CardMixin() {
    name = "Alloy Myr";
    texts = { "colorless", "artifact", "creature", "myr" };
    cmc = 3;
    cost = ManaPool(std::array < unsigned int, 6 > {{3, 0, 0, 0, 0, 0}});
    power = 2;
    toughness = 2;
};

void AlloyMyr::apply_base_modifiers(Game* g, Player* p, Permanent* m) {
    m->abilities.push_back(&TapForAnyManaAbility::instance);
}

/// Lands
#define LAND_MIXIN_MACRO(TYPE) \
CardMixin<TYPE>::CardMixin() { \
    name = #TYPE; \
    texts = { "colorless", "land", "basicland" }; \
    cmc = 0; \
    power = 0; \
    toughness = 0; \
}

LAND_MIXIN_MACRO(Forest);
LAND_MIXIN_MACRO(Island);
LAND_MIXIN_MACRO(Mountain);
LAND_MIXIN_MACRO(Swamp);
LAND_MIXIN_MACRO(Plains);

//////////////

CardMixin<GiantGrowth>::CardMixin() {
    name = "Giant Growth";
    texts = { "green", "instant" };
    cmc = 1;
    cost = ManaPool(std::array < unsigned int, 6 > {{0, 1, 0, 0, 0, 0}});
    power = 0;
    toughness = 0;
};

struct GiantGrowthModifier : TillEndOfTurnL7Mixin<GiantGrowthModifier> {
    GiantGrowthModifier(Game* g) : TillEndOfTurnL7Mixin < GiantGrowthModifier >(g) {}

    int power(int prev) const { return prev + 3; }
    int toughness(int prev) const { return prev + 3; }
};

void GiantGrowth::enact(Game* g, Player* p, Permanent* ct) {
    if (!ct->has_text("creature")) {
        std::cerr << "WARNING: giant growth cast on non-creature" << std::endl;
        return;
    }

    GiantGrowthModifier::instance(g)->attach(ct);
}
