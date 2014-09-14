#pragma once

#include "card.hpp"

template<class Derived, class Base = Card>
struct CardMixin : Base
{
    CardMixin();

    static const Derived instance;
};

template<class Derived, class Base>
const Derived CardMixin<Derived, Base>::instance = {};