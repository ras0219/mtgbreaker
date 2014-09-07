#pragma once

#include "game.hpp"
#include "card.hpp"
#include "action.hpp"
#include "stackable.hpp"

template<class Derived, class Base = Card>
struct CreatureMixin : Base
{
    struct CastSpell* cast_from_hand(std::vector<Card*> mana) {
        Stackable* stackable = make_stackable(static_cast<Derived*>(this), [](Game* g, Derived* c)
        {
            g->battlefield.push_back(c);
        });
        return new CastSpell(this, stackable, mana);
    }
};

template<class Derived, class Base = CardMixin<Derived>>
using CreatureMixinEx = CreatureMixin < Derived, Base >;
