#pragma once

#include "game.hpp"
#include "card.hpp"
#include "action.hpp"
#include "stackable.hpp"

template<class Derived, class Base = Card>
struct LandMixin : Base
{
    struct PlayLandAction* playland_from_hand() {
        return new PlayLandAction(this);
    }
};

template<class Derived, class Base = CardMixin<Derived>>
using LandMixinEx = LandMixin < Derived, Base > ;
