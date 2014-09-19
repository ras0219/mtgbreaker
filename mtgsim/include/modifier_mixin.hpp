#pragma once

#include "utility.hpp"
#include "modifier.hpp"

#include <map>

using L7PlusModifier = IMulti < Modifier, L7Modifier > ;
using L3PlusModifier = IMulti < Modifier, L3Modifier >;
using L37PlusModifier = IMulti < Modifier, L3Modifier, L7Modifier >;

template<class Derived, class Base>
struct BasicModifierMixin : Base {
    static_assert(std::is_base_of<Game::Detach, Base>::value, "BasicModifierMixin requires Game::Detach base");
    static_assert(std::is_base_of<Permanent::Detach, Base>::value, "BasicModifierMixin requires Permanent::Detach base");

    static Derived* instance(Game* g) {
        auto it = instances_map.find(g);
        if (it != instances_map.end())
            return it->second;
        return instances_map.emplace(g, new Derived{ g }).first->second;
    }

    BasicModifierMixin(Game* g) : m_g(g) {
        g->add<Game::Detach>(this);
    }

    // Interface for Applicators (this should not be overridden)
    void attach(Permanent* p) {
        affecteds.push_back(p);
        p->add<Permanent::Detach>(this);
        self()->static_attach(p);
    }

    // Game::Detach
    void detach(Game* g) final {
        for (auto x : affecteds) {
            x->rem<Permanent::Detach>(this);
        }
        self()->static_detach(g);
        instances_map.erase(g);
        delete this;
    }

    // Permanent::Detach
    void detach(Permanent* p) final {
        static_detach(p);
        nstd::unstable_erase_first(affecteds, p);
    }

    // Static Polymorphism chaining the above impls
    void static_attach(Permanent* x) {}
    void static_detach(Permanent* x) {}
    void static_detach(Game* x) {}

protected:
    Game* const m_g;
    std::vector<Permanent*> affecteds;

private:
    Derived* self() { return static_cast<Derived*>(this); }
    Derived const* self() const { return static_cast<Derived const*>(this); }

    static std::map<Game*, Derived*> instances_map;
};

template<class Derived, class Base>
std::map<Game*, Derived*> BasicModifierMixin<Derived, Base>::instances_map;

template<class Derived, class Base = BasicModifierMixin<Derived, IMulti<EndOfTurnTrigger, Game::Detach, Permanent::Detach, L7Modifier>>>
struct TillEndOfTurnL7Mixin : Base {
    TillEndOfTurnL7Mixin(Game* g) : Base{ g } {
        g->add<EndOfTurnTrigger>(this);
    }

    // EndOfTurnTrigger interface
    void end_of_turn(Game* g) {
        for (auto x : affecteds) {
            x->rem<Permanent::Detach>(this);
            x->rem<const L7Modifier>(this);
        }
        affecteds.clear();
    }

    void static_attach(Permanent* p) {
        Base::static_attach(p);
        p->add<const L7Modifier>(this);
    }

    void static_detach(Game* g) {
        Base::static_detach(g);
        for (auto x : affecteds) {
            x->rem<const L7Modifier>(this);
        }
    }

private:
    Derived* self() { return static_cast<Derived*>(this); }
    Derived const* self() const { return static_cast<Derived const*>(this); }
};