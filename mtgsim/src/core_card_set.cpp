#include "core_card_set.hpp"
#include "utility.hpp"
#include "game.hpp"
#include "player.hpp"
#include "card_info.hpp"
#include "modifier.hpp"
#include "modifier_mixin.hpp"

template<>
const CardInfo CardMixin<ChargingBadger>::info_data = {
    "chargingbadger",
    "Charging Badger",
    { "green", "creature", "badger" },
    { "trample" },
    1,
    ManaPool(std::array<unsigned int, 6>{{0, 1, 0, 0, 0, 0}}),
    1,
    1
};

template<>
const CardInfo CardMixin<WalkingCorpse>::info_data = {
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
const CardInfo CardMixin<TyphoidRats>::info_data = {
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
const CardInfo CardMixin<BorderlandMarauder>::info_data = {
    "borderlandmarauder",
    "Borderland Marauder",
    { "red", "creature", "human", "warrior" },
    {},
    2,
    ManaPool(std::array<unsigned int, 6>{{1, 0, 0, 1, 0, 0}}),
    1,
    2
};

struct BorderlandMarauderModifier : EndOfTurnModifierMixin<BorderlandMarauderModifier, L7PlusModifier> {
    void end_of_turn(Game* g, Card* c) {
        while (applications > 0) {
            c->rem_mod(static_cast<L7Modifier*>(this));
            --applications;
        }
    }
    void when_attacks(Game* g, Card* c) {
        ++applications;
        c->add_mod(static_cast<L7Modifier*>(this));
    }

    // L7 stuff
    int power(int prev) const { return prev + 2; }
    int toughness(int prev) const { return prev; }

private:
    int applications = 0;
};

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
const CardInfo CardMixin<AlloyMyr>::info_data = {
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


/// Lands
template<>
const CardInfo CardMixin<Forest>::info_data = {
    "forest",
    "Forest",
    { "colorless", "land", "basicland" },
    {},
    0,
    SMP<>(),
    0,
    0
};

template<>
const CardInfo CardMixin<Swamp>::info_data = {
    "swamp",
    "Swamp",
    { "colorless", "land", "basicland" },
    {},
    0,
    SMP<>(),
    0,
    0
};

template<>
const CardInfo CardMixin<Mountain>::info_data = {
    "mountain",
    "Mountain",
    { "colorless", "land", "basicland" },
    {},
    0,
    SMP<>(),
    0,
    0
};

template<>
const CardInfo CardMixin<Island>::info_data = {
    "island",
    "Island",
    { "colorless", "land", "basicland" },
    {},
    0,
    SMP<>(),
    0,
    0
};

template<>
const CardInfo CardMixin<Plains>::info_data = {
    "plains",
    "Plains",
    { "colorless", "land", "basicland" },
    {},
    0,
    SMP<>(),
    0,
    0
};

//////////////

template<>
const CardInfo CardMixin<GiantGrowth>::info_data = {
    "giantgrowth",
    "Giant Growth",
    { "green", "instant" },
    {},
    1,
    ManaPool(std::array<unsigned int, 6>{{0, 1, 0, 0, 0, 0}}),
    0,
    0
};

struct GiantGrowthModifier : Modifier, L7Modifier {
    void end_of_turn(Game* g, Card* c) {
        c->rem_mod(static_cast<L7Modifier*>(this));
        pending_removal = true;
    }
    void destroyed(Game* g, Card* c) {
        c->rem_mod(static_cast<L7Modifier*>(this));
        pending_removal = true;
    }
    void removed_from_play(Game* g, Card* c) {
        c->rem_mod(static_cast<L7Modifier*>(this));
        pending_removal = true;
    }

    int power(int prev) const { return prev + 3; }
    int toughness(int prev) const { return prev + 3; }
};

void GiantGrowth::enact(Game* g, Player* p, Card* ct) {
    if (!ct->has_text("creature")) {
        std::cerr << "WARNING: giant growth cast on non-creature" << std::endl;
        return;
    }

    auto ggm = new GiantGrowthModifier;

    ct->add_mod(static_cast<Modifier*>(ggm));
    ct->add_mod(static_cast<L7Modifier*>(ggm));
}
