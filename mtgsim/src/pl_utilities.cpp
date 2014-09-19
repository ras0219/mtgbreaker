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
    std::sort(p->hand.begin(), p->hand.end(), [](const Card* c1, const Card* c2) { return c1->cmc > c2->cmc; });
}

std::vector<const Card*> find_lands(Player* p)
{
    std::vector<const Card*> ret;
    ret.reserve(p->hand.size());
    for (auto c : p->hand)
        if (c->has_text("land"))
            ret.push_back(c);
    return ret;
}

Action* play_land(const Card* c)
{
    if (c == &Forest::instance)
        return card_cast<Forest>(c)->play();
    if (c == &Swamp::instance)
        return card_cast<Swamp>(c)->play();
    if (c == &Island::instance)
        return card_cast<Island>(c)->play();
    if (c == &Plains::instance)
        return card_cast<Plains>(c)->play();
    if (c == &Mountain::instance)
        return card_cast<Mountain>(c)->play();
    return nullptr;
}
void tap_land(Game* g, Player* p, Permanent* c)
{
    if (c->card == &Forest::instance)
        return TapForManaAbility<ManaPool::GREEN>::tap_for_mana(g, p, c);
    if (c->card == &Swamp::instance)
        return TapForManaAbility<ManaPool::BLACK>::tap_for_mana(g, p, c);
    if (c->card == &Plains::instance)
        return TapForManaAbility<ManaPool::WHITE>::tap_for_mana(g, p, c);
    if (c->card == &Mountain::instance)
        return TapForManaAbility<ManaPool::RED>::tap_for_mana(g, p, c);
    if (c->card == &Island::instance)
        return TapForManaAbility<ManaPool::BLUE>::tap_for_mana(g, p, c);
}

std::vector<Permanent*> tappable_lands(Game* g, Player* p)
{
	std::vector<Permanent*> valids;

	for (auto c : g->battlefield) {
		if (c->controller != p) continue;
		if (c->tapped) continue;
		if (!c->has_text("land")) continue;
		valids.push_back(c);
	};

	return valids;
}

ManaPool::Type type_of_land(const Card* c)
{
    if (c == &Forest::instance)
        return ManaPool::GREEN;
    if (c == &Swamp::instance)
        return ManaPool::BLACK;
    if (c == &Plains::instance)
        return ManaPool::WHITE;
    if (c == &Mountain::instance)
        return ManaPool::RED;
    if (c == &Island::instance)
        return ManaPool::BLUE;
	throw std::runtime_error("Not a land");
}

ManaPool value_of_tappable_lands(Game* g, Player* p)
{
	ManaPool value;
	auto valids = tappable_lands(g, p);

	for (auto c : valids)
	{
		value[type_of_land(c->card)]++;
	}

	return value;
}

bool tap_required_lands(Game* g, Player* p, const Card* c)
{
	ManaPool empty;
	ManaPool required = c->cost;

	if (required > value_of_tappable_lands(g, p))
		return false;

	auto valids = tappable_lands(g, p);

    for (auto valid : valids)
	{
		if (required[type_of_land(valid->card)] > 0)
		{
			tap_land(g, p, valid);
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

const Card* find_playable_creature_with_attributes(Game* g, Player* p, std::function<bool(const Card*, const Card*)> cmp)
{
	std::vector<const Card*> &hand = p->hand;
	std::vector<const Card*> valids;

	ManaPool potential_mana = p->mana + value_of_tappable_lands(g, p);

	auto is_valid_playable_creature = [potential_mana, p](const Card* c) {
		if (c == nullptr) return false;
		if (!c->has_text("creature")) return false;
		return potential_mana >= c->cost;
	};

	std::copy_if(hand.begin(), hand.end(), std::back_inserter(valids), is_valid_playable_creature);
	
	auto ret = std::max_element(valids.begin(), valids.end(), cmp);
	if (ret == valids.end())
	{
		return nullptr;
	}
	return *ret;
}

Action* play_creature(Player* p, const Card* c)
{
#define PLAY_CREATURE_MACRO(TYPE) if (c == &TYPE::instance) return TYPE::cast_from_hand(p)
    PLAY_CREATURE_MACRO(ChargingBadger);
    PLAY_CREATURE_MACRO(WalkingCorpse);
    PLAY_CREATURE_MACRO(TyphoidRats);
    PLAY_CREATURE_MACRO(AlloyMyr);
#undef PLAY_CREATURE_MACRO
    return nullptr;
}
