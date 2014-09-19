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
            auto m = new Permanent(&Derived::instance, p);
            g->battlefield.push_back(m);
        });
        return new CastSpellAction(&Derived::instance, stackable);
    }
};

template<class Derived, class Base = CardMixin<Derived>>
struct CreatureMixinEx : Base
{
    static CastSpellAction* cast_from_hand(Player* p) {
        Stackable* stackable = make_stackable(&Derived::instance, [p](Game* g)
        {
            auto m = new Permanent(&Derived::instance, p);
            Derived::apply_base_modifiers(g, p, m);
            g->battlefield.push_back(m);
        });
        return new CastSpellAction(&Derived::instance, stackable);
    }

    static void apply_base_modifiers(Game* g, Player* p, Permanent* m) {}
};
