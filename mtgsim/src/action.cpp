#include "action.hpp"
#include "utility.hpp"
#include "game.hpp"
#include "card.hpp"
#include "player.hpp"
#include <algorithm>
#include <stdexcept>
#include <cassert>

const char* CastSpellAction::check(Game* g, Player* p)
{
    CHECK_RETURN(g);
    CHECK_RETURN(p);
    auto it = std::find(p->hand.begin(), p->hand.end(), card);
    CHECK_RETURN(it != p->hand.end());
    if (!card->has_text("instant") || !card->has_text("flash"))
    {
        CHECK_RETURN(g->state == Game::PRECOMBAT_MAIN || g->state == Game::POSTCOMBAT_MAIN);
        CHECK_RETURN(g->active_player == p);
        CHECK_RETURN(g->stack.empty());
    }
    CHECK_RETURN(p->mana >= card->cost);
    return nullptr;
}

void CastSpellAction::enact(Game* g, Player* p)
{
    assert(check(g, p) == nullptr);

    // Remove the card from the player's hand
    auto it = std::find(p->hand.begin(), p->hand.end(), card);
    std::iter_swap(it, p->hand.end() - 1);
    p->hand.pop_back();

    // Pay the cost
    p->mana -= card->cost;

    // Put it onto the stack
    g->stack.push_back(stackable);

    // Priority stays with me
}
