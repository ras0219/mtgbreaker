#pragma once

#include "card.hpp"
#include "card_class_static.hpp"

template<class Derived, class Base = Card>
struct CardMixin : Base
{
    virtual const CardInfo& info() const override
    {
        return info_data;
    }
    virtual const CardClass& cardclass() const override
    {
        return cardclass_data;
    }

    static const CardClassStatic<Derived> cardclass_data;
    static const CardInfo info_data;
};


template<class Derived, class Base>
const CardClassStatic<Derived> CardMixin<Derived, Base>::cardclass_data
#if !defined(_MSC_VER)
// this is why we can't have nice things...
{}
#endif
;
