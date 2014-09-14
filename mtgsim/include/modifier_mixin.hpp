#pragma once

#include "utility.hpp"
#include "modifier.hpp"

using L7PlusModifier = IMulti < Modifier, L7Modifier > ;
using L3PlusModifier = IMulti < Modifier, L3Modifier >;
using L37PlusModifier = IMulti < Modifier, L3Modifier, L7Modifier >;

template<class Derived, class Base = Modifier>
struct EndOfTurnModifierMixin : Base {
    virtual void destroyed(Game* g, Permanent* c) { self()->end_of_turn(g, c); }
    virtual void removed_from_play(Game* g, Permanent* c) { self()->end_of_turn(g, c); }

private:
    Derived* self() { return static_cast<Derived*>(this); }
    Derived const* self() const { return static_cast<Derived const*>(this); }
};
