#pragma once

#include "card.hpp"
#include "creature.hpp"
#include "land.hpp"
#include "spell.hpp"

/// Mixin which implements a card with the text:
/// <Derived> deals <DMG> damage to target creature or player.
template<unsigned int DMG, class Derived, class Base = SpellMixinEx<Derived>>
struct BurnSpellMixin : Base {
    template<class, class>
    friend struct SpellMixin;
private:
    void enact(Game* g, Player* p, Card* target)
    {
        if (!target->info().has("creature"))
            throw std::runtime_error("Target is not a creature");
        if (g->battlefield.end() == g->find_in_battlefield(target))
            throw std::runtime_error("Target is not in play");
        target->apply_damage(g, DMG);
    }
    void enact(Game* g, Player* p, Player* target)
    {
        target->apply_damage(g, DMG);
    }
};

struct LightningBolt : BurnSpellMixin<3, LightningBolt> { };
struct VolcanicHammer : BurnSpellMixin<3, VolcanicHammer> { };
struct Shock : BurnSpellMixin<2, Shock> { };

struct LavaAxe : SpellMixinEx<LavaAxe> {
    template<class, class>
    friend struct SpellMixin;
private:
    void enact(Game* g, Player* p, Player* target);
};

#if 0
struct BarbedLightning : SpellMixinEx<BarbedLightning> {
    template<class, class>
    friend struct SpellMixin;
private:
    void enact(Game* g, Player* p, Card* target);
    void enact(Game* g, Player* p, Player* target);
    void enact(Game* g, Player* p, Card* ct, Player* pt);
};
#endif
