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

void tap_land(Game* g, Player* p, Card* c)
{
	auto id = c->info().id;
	if (id == "forest")
		return card_cast<Forest>(c)->tap_for_mana(g, p);
	if (id == "swamp")
		return card_cast<Swamp>(c)->tap_for_mana(g, p);
	if (id == "mountain")
		return card_cast<Mountain>(c)->tap_for_mana(g, p);
	if (id == "island")
		return card_cast<Island>(c)->tap_for_mana(g, p);
	if (id == "plains")
		return card_cast<Plains>(c)->tap_for_mana(g, p);
}

std::vector<Card*> tappable_lands(Game* g, Player* p)
{
	std::vector<Card*> valids;

	for (auto c : g->battlefield) {
		if (c->controller != p) continue;
		if (c->tapped) continue;
		if (!c->info().has("land")) continue;
		valids.push_back(c);
	};

	return valids;
}

ManaPool::Type type_of_land(Card* c)
{
	auto id = c->info().id;
	if (id == "forest")
		return ManaPool::GREEN;
	else if (id == "swamp")
		return ManaPool::BLACK;
	else if (id == "mountain")
		return ManaPool::RED;
	else if (id == "island")
		return ManaPool::BLUE;
	else if (id == "plains")
		return ManaPool::WHITE;
	throw std::runtime_error("Not a land");
}

ManaPool value_of_tappable_lands(Game* g, Player* p)
{
	ManaPool value;
	std::vector<Card*> valids = tappable_lands(g, p);

	for (auto c : valids)
	{
		value[type_of_land(c)]++;
	}

	return value;
}

bool tap_required_lands(Game* g, Player* p, Card* c)
{
	ManaPool empty;
	ManaPool required = c->info().cost;

	if (required > value_of_tappable_lands(g, p))
		return false;

	std::vector<Card*> valids = tappable_lands(g, p);

	for (auto it = valids.begin(); it != valids.end(); ++it)
	{
		if (required[type_of_land(*it)] > 0)
		{
			tap_land(g, p, *it);
		}
	}
	for (auto it = valids.begin(); it != valids.end(); ++it)
	{
		if (!(*it)->tapped && required[ManaPool::COLORLESS] > 0)
		{
			tap_land(g, p, *it);
		}
	}
	
	return true;
}

bool can_play_creature(Game* g, Player* p)
{
	return (g->state == Game::PRECOMBAT_MAIN || g->state == Game::POSTCOMBAT_MAIN)
		&& g->active_player == p
		&& g->stack.empty();
}

Card* find_playable_creature_with_attributes(Game* g, Player* p, std::function<bool(Card*, Card*)> cmp)
{
	std::vector<Card*> &hand = p->hand;
	std::vector<Card*> valids;

	ManaPool potential_mana = p->mana + value_of_tappable_lands(g, p);

	auto is_valid_playable_creature = [potential_mana, p](Card* c) {
		if (c == nullptr) return false;
		if (!c->info().has("creature")) return false;
		return potential_mana >= c->info().cost;
	};

	std::copy_if(hand.begin(), hand.end(), std::back_inserter(valids), is_valid_playable_creature);
	
	auto ret = std::max_element(valids.begin(), valids.end(), cmp);
	if (ret == valids.end())
	{
		return nullptr;
	}
	return *ret;
}

Action* play_creature(Card* c)
{
	auto id = c->info().id;
	if (id == "chargingbadger")
		return card_cast<ChargingBadger>(c)->cast_from_hand();
	if (id == "walkingcorpse")
		return card_cast<WalkingCorpse>(c)->cast_from_hand();
	if (id == "typhoidrats")
		return card_cast<TyphoidRats>(c)->cast_from_hand();
	if (id == "alloymyr")
		return card_cast<AlloyMyr>(c)->cast_from_hand();
	return nullptr;
}
