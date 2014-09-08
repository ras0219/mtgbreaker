#pragma once

#include "card.hpp"

struct SpellStackable;

struct Stackable
{
    virtual ~Stackable() {}
    virtual void resolve(struct Game* g) = 0;

    virtual SpellStackable* as_spell() { return nullptr; }
};

struct SpellStackable : Stackable
{
    SpellStackable(Card* c) : card(c) {}
    virtual Card* card_target1() { return ct1; }
    virtual Card* card_target2() { return ct2; }
    virtual Player* player_target1() { return p1; }
    virtual Player* player_target2() { return p2; }

    Card* card;

public:
    Card* ct1 = nullptr;
    Card* ct2 = nullptr;
    Player* p1 = nullptr;
    Player* p2 = nullptr;
};

template<class C, class F, class=std::enable_if_t<!std::is_same<C, Card>::value> >
struct FunctorSpellStackable : SpellStackable
{
    FunctorSpellStackable(C* c, F f) : SpellStackable(c), func(std::move(f)) {}

    virtual void resolve(struct Game* g) override {
        func(g, static_cast<C*>(card));
    }

    F func;
};

template<class C, class F>
SpellStackable* make_stackable(C* c, F f) {
    return new FunctorSpellStackable<C, F>(c, std::move(f));
}

