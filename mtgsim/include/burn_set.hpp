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
        if (!target->has_text("creature"))
        {
            std::cerr << "WARNING: Target is not a creature" << std::endl;
            return;
        }
        if (g->is_in_play(target))
        {
            std::cerr << "WARNING: Target is not in play" << std::endl;
            return;
        }
        target->apply_damage(g, this, DMG);
    }
    void enact(Game* g, Player* p, Player* target)
    {
        target->apply_damage(g, this, DMG);
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

struct LavaSpike : SpellMixinEx<LavaSpike> {
    template<class, class>
    friend struct SpellMixin;
private:
    void enact(Game* g, Player* p, Player* target);
};

struct SearingBlaze : SpellMixinEx<SearingBlaze> {
    template<class, class>
    friend struct SpellMixin;
private:
    void enact(Game* g, Player* p, Card* ct, Player* pt);
};

struct VolcanicFallout : SpellMixinEx < VolcanicFallout > {
    template<class, class>
    friend struct SpellMixin;
private:
    void enact(Game* g, Player* p);
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
