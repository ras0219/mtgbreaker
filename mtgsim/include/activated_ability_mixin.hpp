#pragma once

#include "activated_ability.hpp"

template<class Derived, class Base = ActivatedAbility>
struct ActivatedAbilityMixin : Base {
    static const Derived instance;
};
template<class Derived, class Base>
const Derived ActivatedAbilityMixin<Derived, Base>::instance;