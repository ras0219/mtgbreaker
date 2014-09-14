#pragma once

#include "activated_ability_mixin.hpp"
#include "mana.hpp"

struct Game;
struct Player;
struct Permanent;

namespace detail {
    void tap_for_mana_impl(Game* g, Player* p, Permanent* m, ManaPool::Type t);
}

template<ManaPool::Type T>
struct TapForManaAbility : ActivatedAbilityMixin<TapForManaAbility<T>> {
    static void tap_for_mana(Game* g, Player* p, Permanent* c) { detail::tap_for_mana_impl(g, p, c, T); }
};
