#pragma once

#include "card_class.hpp"

template<class C>
struct CardClassStatic : CardClass
{
    virtual const CardInfo& info() const override
    {
        return C::info_data;
    }
    virtual Card* create(Player* p) const override
    {
        auto c = new C;
        c->owner = p;
        c->controller = p;
        return c;
    }
};
