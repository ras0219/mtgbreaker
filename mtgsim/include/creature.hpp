#pragma once

#include "game.hpp"
#include "card.hpp"
#include "action.hpp"
#include "stackable.hpp"

template<class Derived>
struct CreatureStackable
{

};

template<class Derived, class Base = Card>
struct CreatureMixin : Base
{
    struct CastSpellAction* cast_from_hand() {
        Stackable* stackable = make_stackable(static_cast<Derived*>(this), [](Game* g, Derived* c)
        {
            g->battlefield.push_back(c);
        });
        return new CastSpellAction(this, stackable);
    }
};

template<class Derived, class Base = CardMixin<Derived>>
using CreatureMixinEx = CreatureMixin < Derived, Base >;
