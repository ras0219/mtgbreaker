#include "utility.hpp"
#include "action.hpp"
#include "game.hpp"
#include <algorithm>
#include <stdexcept>
#include <cassert>

const char* PlayLandAction::check(Game* g, Player* p)
{
    CHECK_RETURN(g);
    CHECK_RETURN(p);
    CHECK_RETURN(g->state == Game::PRECOMBAT_MAIN || g->state == Game::POSTCOMBAT_MAIN);
    CHECK_RETURN(g->active_player == p);
    CHECK_RETURN(g->stack.empty());
    CHECK_RETURN(card->owner == p);
    auto it = std::find(p->hand.begin(), p->hand.end(), card);
    CHECK_RETURN(it != p->hand.end());
    CHECK_RETURN(g->lands_played == 0);
    return nullptr;
}

void PlayLandAction::enact(Game* g, Player* p)
{
    assert(check(g, p) == nullptr);
    // Remove the land from the player's hand
    auto it = std::find(p->hand.begin(), p->hand.end(), card);
    std::swap(*it, p->hand.back());
    p->hand.pop_back();

    // Put it into play
    g->battlefield.push_back(card);
    g->lands_played = 1;
}

void gain_mana(Card* c, ManaPool& mpool) {
    auto& i = c->info();
    if (i.id == "forest")
        mpool[ManaPool::GREEN]++;
    else if (i.id == "plains")
        mpool[ManaPool::WHITE]++;
    else if (i.id == "swamp")
        mpool[ManaPool::BLACK]++;
    else if (i.id == "island")
        mpool[ManaPool::BLUE]++;
    else if (i.id == "mountain")
        mpool[ManaPool::RED]++;
}

const char* check_cost(Game* g, Player* p, ManaPool const& cost, std::vector<Card*> const& mana)
{
    ManaPool mpool = p->mana;

    auto& bf = g->battlefield;
    for (auto m : mana)
    {
        // Does the player own it?
        CHECK_RETURN(m->owner != p);
        // Is it in play?
        CHECK_RETURN(std::find(bf.begin(), bf.end(), m) != bf.end());
        // Is it not tapped?
        CHECK_RETURN(!m->tapped);
        // Is it a basic land?
        auto& i = m->info();
        CHECK_RETURN(i.id == "forest" || i.id == "plains" || i.id == "swamp" || i.id == "island" || i.id == "mountain");
        gain_mana(m, mpool);
    }

    CHECK_RETURN(mpool >= cost);
    return nullptr;
}

const char* CastSpell::check(Game* g, Player* p)
{
    CHECK_RETURN(g);
    CHECK_RETURN(p);
    CHECK_RETURN(card->owner == p);
    auto it = std::find(p->hand.begin(), p->hand.end(), card);
    CHECK_RETURN(it != p->hand.end());
    auto& info = card->info();
    if (!info.has("instant"))
    {
        CHECK_RETURN(g->state == Game::PRECOMBAT_MAIN || g->state == Game::POSTCOMBAT_MAIN);
        CHECK_RETURN(g->active_player == p);
        CHECK_RETURN(g->stack.empty());
    }
    auto r = check_cost(g, p, info.cost, mana);
    if (r) return r;
    // don't handle other costs yet
    CHECK_RETURN(other.empty());
    return nullptr;
}

void CastSpell::enact(Game* g, Player* p)
{
    assert(check(g, p) == nullptr);

    auto& i = card->info();

    // Remove the card from the player's hand
    auto it = std::find(p->hand.begin(), p->hand.end(), card);
    std::swap(*it, p->hand.back());
    p->hand.pop_back();

    // Tap Mana and Mana-Equivalents
    for (auto m : mana)
    {
        m->tapped = true;
        gain_mana(m, p->mana);
    }
    // Pay the cost
    p->mana -= i.cost;

    // Put it onto the stack
    g->stack.push_back(stackable);

    // Priority stays with me
}
