#pragma once

#include "game.hpp"
#include "card.hpp"
#include "action.hpp"
#include "stackable.hpp"
#include "card_mixin.hpp"

void tap_for_mana_impl(Game* g, Player* p, Card* c);

template<class Derived, class Base = Card>
struct LandMixin : Base
{
    struct PlayLandAction* playland_from_hand() {
        return new PlayLandAction(this);
    }

    void tap_for_mana(Game* g, Player* p) { tap_for_mana_impl(g, p, this); }
};

template<class Derived, class Base = CardMixin<Derived>>
using LandMixinEx = LandMixin < Derived, Base > ;
