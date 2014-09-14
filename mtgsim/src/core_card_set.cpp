#include "core_card_set.hpp"
#include "utility.hpp"
#include "game.hpp"
#include "player.hpp"
#include "modifier.hpp"
#include "modifier_mixin.hpp"

CardMixin<ChargingBadger>::CardMixin() {
    name = "Charging Badger";
    texts = { "green", "creature", "badger" };
    abilities = { "trample" };
    cmc = 1;
    cost = ManaPool(std::array < unsigned int, 6 > {{0, 1, 0, 0, 0, 0}});
    power = 1;
    toughness = 1;
};

#if 0
template<>
const WalkingCorpse CardMixin<WalkingCorpse>::instance = Card{
    "walkingcorpse",
    "Walking Corpse",
    { "black", "creature", "zombie" },
    {},
    2,
    ManaPool(std::array<unsigned int, 6>{{1, 0, 1, 0, 0, 0}}),
    2,
    2
};

template<>
const TyphoidRats CardMixin<TyphoidRats>::instance = {
    "typhoidrats",
    "Typhoid Rats",
    { "black", "creature", "rat" },
    { "deathtouch" },
    1,
    ManaPool(std::array<unsigned int, 6>{{0, 0, 1, 0, 0, 0}}),
    1,
    1
};
/////////////////////////////////////
template<>
const BorderlandMarauder CardMixin<BorderlandMarauder>::instance = {
    "borderlandmarauder",
    "Borderland Marauder",
    { "red", "creature", "human", "warrior" },
    {},
    2,
    ManaPool(std::array<unsigned int, 6>{{1, 0, 0, 1, 0, 0}}),
    1,
    2
};

struct BorderlandMarauderBuffStackable : Stackable {
    BorderlandMarauderBuffStackable(Card* bm, BorderlandMarauderModifier* l7m) : c(bm), l7(l7m) {}

    void resolve(Game* g);

    Card* c;
    BorderlandMarauderModifier* l7;
};

struct BorderlandMarauderModifier : EndOfTurnModifierMixin<BorderlandMarauderModifier, L7PlusModifier> {
    void end_of_turn(Game* g, Card* c) {
        while (applications > 0) {
            c->rem_l7(this);
            --applications;
        }
    }
    void when_attacks(Game* g, Card* c) {
        static_cast<BorderlandMarauder*>(c)->trigger(new BorderlandMarauderBuffStackable{c, this});
    }

    // L7 stuff
    int power(int prev) const { return prev + 2; }
    int toughness(int prev) const { return prev; }

private:
    int applications = 0;
};

void BorderlandMarauderBuffStackable::resolve(Game* g) {
    c->add_l7(l7);
}

BorderlandMarauder::BorderlandMarauder() : mod{ std::make_unique<BorderlandMarauderModifier>() }
{
    add_mod(static_cast<Modifier*>(mod.get()));
}
BorderlandMarauder::~BorderlandMarauder()
{
    rem_mod(static_cast<Modifier*>(mod.get()));
}

/////////////////////////////////////

template<>
const AlloyMyr CardMixin<AlloyMyr>::instance = {
    "alloymyr",
    "Alloy Myr",
    { "colorless", "artifact", "creature", "myr" },
    {},
    3,
    ManaPool(std::array<unsigned int, 6>{{3, 0, 0, 0, 0, 0}}),
    2,
    2
};

void AlloyMyr::tap_for_mana(Game* g, Player* p, ManaPool::Type t) {
    auto msg = can_tap(g, p);
    if (msg)
        throw std::runtime_error(msg);
    if (sick)
        throw std::runtime_error("Cannot tap creatures with summoning sickness");

    tap(g, p);
    p->mana += t;
}

#endif
/// Lands
CardMixin<Forest>::CardMixin() {
    name = "Forest";
    texts = { "colorless", "land", "basicland" };
    cmc = 0;
    power = 0;
    toughness = 0;
};

CardMixin<Mountain>::CardMixin() {
    name = "Mountain";
    texts = { "colorless", "land", "basicland" };
    cmc = 0;
    power = 0;
    toughness = 0;
};

CardMixin<Swamp>::CardMixin() {
    name = "Swamp";
    texts = { "colorless", "land", "basicland" };
    cmc = 0;
    power = 0;
    toughness = 0;
};

CardMixin<Plains>::CardMixin() {
    name = "Plains";
    texts = { "colorless", "land", "basicland" };
    cmc = 0;
    power = 0;
    toughness = 0;
};

CardMixin<Island>::CardMixin() {
    name = "Island";
    texts = { "colorless", "land", "basicland" };
    cmc = 0;
    power = 0;
    toughness = 0;
};

//////////////

CardMixin<GiantGrowth>::CardMixin() {
    name = "Giant Growth";
    texts = { "green", "instant" };
    cmc = 1;
    cost = ManaPool(std::array < unsigned int, 6 > {{0, 1, 0, 0, 0, 0}});
    power = 0;
    toughness = 0;
};

struct GiantGrowthModifier : EndOfTurnModifierMixin<GiantGrowthModifier, L7PlusModifier> {
    void end_of_turn(Game* g, Permanent* c) {
        c->rem_l7(this);
        pending_removal = true;
    }

    int power(int prev) const { return prev + 3; }
    int toughness(int prev) const { return prev + 3; }
};

void GiantGrowth::enact(Game* g, Player* p, Permanent* ct) {
    if (!ct->has_text("creature")) {
        std::cerr << "WARNING: giant growth cast on non-creature" << std::endl;
        return;
    }

    auto ggm = new GiantGrowthModifier;

    ct->add_mod(ggm);
    ct->add_l7(ggm);
}
