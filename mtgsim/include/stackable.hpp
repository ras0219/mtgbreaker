#pragma once

#include "card.hpp"

struct Stackable
{
    virtual ~Stackable() {}
    virtual void resolve(struct Game* g) = 0;

    enum Type
    {
        SPELL
    } type;
};

template<class C>
struct SpellStackable : Stackable
{
    SpellStackable(C* c) : Stackable{ SPELL }, card(c) {}

    C* card;
};

template<class C, class F>
struct FunctorSpellStackable : SpellStackable<C>
{
    FunctorSpellStackable(C* c, F f) : SpellStackable<C>(c), func(std::move(f)) {}

    virtual void resolve(struct Game* g) override {
        func(g, card);
    }

    F func;
};

template<class C, class F>
Stackable* make_stackable(C* c, F f) {
    return new FunctorSpellStackable<C, F>(c, std::move(f));
}

