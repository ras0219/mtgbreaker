#pragma once

#include "game.hpp"
#include "card.hpp"
#include "action.hpp"
#include "stackable.hpp"
#include "card_mixin.hpp"
#include "permanent.hpp"
#include "core_activated_abilities.hpp"

template<class Land>
struct PlayLandAction : Action
{
    static_assert(std::is_base_of<Card, Land>::value, "Land must derived from Card");

    PlayLandAction(const Land* c) : card(c) {}

    const char* check(Game* g, Player* p) {
        CHECK_RETURN(g);
        CHECK_RETURN(p);
        CHECK_RETURN(g->state == Game::PRECOMBAT_MAIN || g->state == Game::POSTCOMBAT_MAIN);
        CHECK_RETURN(g->active_player == p);
        CHECK_RETURN(g->stack.empty());
        auto it = std::find(p->hand.begin(), p->hand.end(), card);
        CHECK_RETURN(it != p->hand.end());
        CHECK_RETURN(g->lands_played == 0);
        return nullptr;
    }
    void enact(Game* g, Player* p) {
        if (check(g, p) != nullptr) {
            std::abort();
        }
        // Create the permanent
        typename Land::Permanent* perm = new typename Land::Permanent(p);

        // Remove the land from the player's hand
        nstd::unstable_erase_first(p->hand, card);

        // Put it into play
        g->battlefield.push_back(perm);
        g->lands_played = 1;
    }

    const Land* card;
};

template<ManaPool::Type T, class Derived, class Base = CardMixin<Derived>>
struct BasicLandMixin : Base
{
    static const ManaPool::Type color = T;

    PlayLandAction<Derived>* play() const {
        return new PlayLandAction<Derived>(self());
    }

protected:
    friend struct PlayLandAction < Derived > ;

    struct LandPermanentMixin : ::Permanent {
        LandPermanentMixin(Player* p) : ::Permanent(&Derived::instance, p)
        {
            abilities.push_back(&TapForManaAbility<T>::instance);
        }

    };

    using Permanent = LandPermanentMixin;

private:
    Derived* self() { return static_cast<Derived*>(this); }
    const Derived* self() const { return static_cast<const Derived*>(this); }
};
