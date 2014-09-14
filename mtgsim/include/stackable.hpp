#pragma once

#include "utility.hpp"
#include "card.hpp"

struct SpellStackable;

struct Stackable
{
    virtual ~Stackable() {}
    virtual void resolve(struct Game* g) = 0;
};

struct SpellStackable : Stackable
{
    SpellStackable(const Card* c) : card(c) {}
    /// All of this is kludge; TODO: find a better way. Probably involving uniquely naming each possible effect.
    virtual Permanent* card_target1() { return ct1; }
    virtual Permanent* card_target2() { return ct2; }
    virtual Player* player_target1() { return p1; }
    virtual Player* player_target2() { return p2; }

    const Card* card;

public:
    Permanent* ct1 = nullptr;
    Permanent* ct2 = nullptr;
    Player* p1 = nullptr;
    Player* p2 = nullptr;
};

template<class F>
struct FunctorSpellStackable : SpellStackable
{
    FunctorSpellStackable(const Card* c, F f) : SpellStackable(c), func(std::move(f)) {}

    virtual void resolve(struct Game* g) override { func(g); }

    F func;
};

template<class F>
SpellStackable* make_stackable(const Card* c, F f) {
    return new FunctorSpellStackable<F>(c, std::move(f));
}

