#pragma once

#include "game.hpp"
#include "card.hpp"
#include "action.hpp"
#include "stackable.hpp"

template<class Derived, class Base = CardMixin<Derived>>
struct SpellMixin : Base
{
    template<class...Args>
    CastSpellAction* cast_from_hand(Player* p, Args...args) const {
        Stackable* stackable = make_stackable(static_cast<const Derived*>(this), [p, args...](Game* g)
        {
            Derived::instance.enact(g, p, args...);
        });
        return new CastSpellAction(this, stackable);
    }
};
