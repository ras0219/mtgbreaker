#include "utility.hpp"
#include "action.hpp"
#include "game.hpp"
#include "player.hpp"
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
    std::iter_swap(it, p->hand.end()-1);
    p->hand.pop_back();

    // Put it into play
    g->battlefield.push_back(card);
    g->lands_played = 1;
}

const char* CastSpellAction::check(Game* g, Player* p)
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
    CHECK_RETURN(p->mana >= info.cost);
    return nullptr;
}

void CastSpellAction::enact(Game* g, Player* p)
{
    assert(check(g, p) == nullptr);

    auto& i = card->info();

    // Remove the card from the player's hand
    auto it = std::find(p->hand.begin(), p->hand.end(), card);
    std::iter_swap(it, p->hand.end() - 1);
    p->hand.pop_back();

    // Pay the cost
    p->mana -= i.cost;

    // Put it onto the stack
    g->stack.push_back(stackable);

    // Priority stays with me
}
