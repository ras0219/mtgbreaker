#include "pl_utilities.hpp"
#include "card.hpp"
#include "player.hpp"
#include "core_card_set.hpp"
#include <algorithm>

bool can_play_land(Game* g, Player* p)
{
    return (g->state == Game::PRECOMBAT_MAIN || g->state == Game::POSTCOMBAT_MAIN)
        && g->active_player == p
        && g->stack.empty()
        && g->lands_played == 0;
}

void sort_hand_by_cmc(Player* p)
{
    std::sort(p->hand.begin(), p->hand.end(), [](Card* c1, Card* c2) { return c1->info().cmc > c2->info().cmc; });
}

std::vector<Card*> find_lands(Player* p)
{
    std::vector<Card*> ret;
    ret.reserve(p->hand.size());
    for (auto c : p->hand)
        if (c->info().has("land"))
            ret.push_back(c);
    return ret;
}

Action* play_land(Card* c)
{
    auto id = c->info().id;
    if (id == "forest")
        return card_cast<Forest>(c)->playland_from_hand();
    if (id == "swamp")
        return card_cast<Swamp>(c)->playland_from_hand();
    if (id == "mountain")
        return card_cast<Mountain>(c)->playland_from_hand();
    if (id == "island")
        return card_cast<Island>(c)->playland_from_hand();
    if (id == "plains")
        return card_cast<Plains>(c)->playland_from_hand();
    return nullptr;
}
