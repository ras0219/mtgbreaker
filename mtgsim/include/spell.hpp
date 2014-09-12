#pragma once

#include "game.hpp"
#include "card.hpp"
#include "action.hpp"
#include "stackable.hpp"

template<class Derived, class Base = Card>
struct SpellMixin : Base
{
    CastSpellAction* cast_from_hand() {
        SpellStackable* stackable = make_stackable(static_cast<Derived*>(this), [](Game* g, Derived* c)
        {
            c->enact(g, c->controller);
        });
        return new CastSpellAction(this, stackable);
    }

    CastSpellAction* cast_from_hand(Card* target) {
        SpellStackable* stackable = make_stackable(static_cast<Derived*>(this), [=](Game* g, Derived* c)
        {
            c->enact(g, c->controller);
        });
        stackable->ct1 = target;
        return new CastSpellAction(this, stackable);
    }

    CastSpellAction* cast_from_hand(Player* target) {
        SpellStackable* stackable = make_stackable(static_cast<Derived*>(this), [=](Game* g, Derived* c)
        {
            c->enact(g, c->controller, target);
        });
        stackable->p1 = target;
        return new CastSpellAction(this, stackable);
    }

    CastSpellAction* cast_from_hand(Card* ct, Player* pt) {
        SpellStackable* stackable = make_stackable(static_cast<Derived*>(this), [=](Game* g, Derived* c)
        {
            c->enact(g, c->controller, ct, pt);
        });
        stackable->p1 = pt;
        stackable->ct1 = ct;
        return new CastSpellAction(this, stackable);
    }

private:
    template<class...Args>
    CastSpellAction* cast_from_hand(Args...args) {
        Stackable* stackable = make_stackable(static_cast<Derived*>(this), [args...](Game* g, Derived* c)
        {
            c->enact(g, c->controller, args...);
        });
        return new CastSpellAction(this, stackable);
    }
};

template<class Derived, class Base = CardMixin<Derived>>
using SpellMixinEx = SpellMixin < Derived, Base >;

