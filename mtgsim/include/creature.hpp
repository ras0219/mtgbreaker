#pragma once

#include "game.hpp"
#include "card.hpp"
#include "action.hpp"
#include "stackable.hpp"
#include "card_mixin.hpp"

template<class Derived, class Base = CardMixin<Derived>>
struct CreatureMixin : Base
{
    static CastSpellAction* cast_from_hand(Player* p) {
        Stackable* stackable = make_stackable(&Derived::instance, [p](Game* g)
        {
            g->battlefield.push_back(new Permanent(&Derived::instance, p));
        });
        return new CastSpellAction(&Derived::instance, stackable);
    }
};
