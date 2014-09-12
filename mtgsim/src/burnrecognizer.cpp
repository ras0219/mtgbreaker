#include "burnrecognizer.hpp"

bool BurnRecognizer::can_recognize(Card* c) {
	return playmap.find(c->info().id) != playmap.end();
}

Action* BurnRecognizer::recognize(Game* g, Player* p, Card* c) {
	auto it = playmap.find(c->info().id);
	if (it == playmap.end())
		return nullptr;
	else
		return it->second(g, p, c);
}

template<>
Action* BurnRecognizer::play_burn<LightningBolt>(Game* g, Player* p, Card* c) {
	return card_cast<LightningBolt>(c)->cast_from_hand(g->other_player(p));
}
template<>
Action* BurnRecognizer::play_burn<VolcanicHammer>(Game* g, Player* p, Card* c) {
	return card_cast<VolcanicHammer>(c)->cast_from_hand(g->other_player(p));
}
template<>
Action* BurnRecognizer::play_burn<LavaAxe>(Game* g, Player* p, Card* c) {
	return card_cast<LavaAxe>(c)->cast_from_hand(g->other_player(p));
}
template<>
Action* BurnRecognizer::play_burn<Shock>(Game* g, Player* p, Card* c) {
	return card_cast<Shock>(c)->cast_from_hand(g->other_player(p));
}
template<>
Action* BurnRecognizer::play_burn<VolcanicFallout>(Game* g, Player* p, Card* c) {
	return card_cast<VolcanicFallout>(c)->cast_from_hand();
}

std::unordered_map<std::string, BurnRecognizer::play_burn_t> BurnRecognizer::playmap =
{
	{ "lavaaxe", BurnRecognizer::play_burn < LavaAxe > },
	{ "volcanichammer", BurnRecognizer::play_burn < VolcanicHammer > },
	{ "lightningbolt", BurnRecognizer::play_burn < LightningBolt> },
	{ "shock", BurnRecognizer::play_burn < Shock > },
	{ "volcanicfallout", BurnRecognizer::play_burn < VolcanicFallout > }
};