#pragma once

#include "card.hpp"
#include "creature.hpp"
#include "land.hpp"
#include "spell.hpp"
#include "player.hpp"

/// Mixin which implements a card with the text:
/// <Derived> deals <DMG> damage to target creature or player.
template<unsigned int DMG, class Derived, class Base = SpellMixin<Derived>>
struct BurnSpellMixin : Base {
    template<class, class>
    friend struct SpellMixin;
private:
    void enact(Game* g, Player* p, Permanent* target) const
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
    void enact(Game* g, Player* p, Player* target) const
    {
        target->apply_damage(g, this, DMG);
    }
};

struct LightningBolt : BurnSpellMixin<3, LightningBolt> { };
struct VolcanicHammer : BurnSpellMixin<3, VolcanicHammer> { };
struct Shock : BurnSpellMixin<2, Shock> { };

struct LavaAxe : SpellMixin<LavaAxe> {
    template<class, class>
    friend struct SpellMixin;
private:
    void enact(Game* g, Player* p, Player* target) const;
};

struct LavaSpike : SpellMixin<LavaSpike> {
    template<class, class>
    friend struct SpellMixin;
private:
    void enact(Game* g, Player* p, Player* target) const;
};

struct SearingBlaze : SpellMixin<SearingBlaze> {
    template<class, class>
    friend struct SpellMixin;
private:
    void enact(Game* g, Player* p, Permanent* ct, Player* pt) const;
};

struct AngerOfTheGods : SpellMixin < AngerOfTheGods > {
    template<class, class>
    friend struct SpellMixin;
private:
    void enact(Game* g, Player* p) const;
};

struct VolcanicFallout : SpellMixin < VolcanicFallout > {
    template<class, class>
    friend struct SpellMixin;
private:
    void enact(Game* g, Player* p) const;
};

#if 0
struct BarbedLightning : SpellMixin<BarbedLightning> {
    template<class, class>
    friend struct SpellMixin;
private:
    void enact(Game* g, Player* p, Card* target);
    void enact(Game* g, Player* p, Player* target);
    void enact(Game* g, Player* p, Card* ct, Player* pt);
};
#endif
