#include "burn_set.hpp"
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

template<class T> struct is_player_burn : std::false_type {};
template<class T> struct is_global_burn : std::false_type {};

template<class T>
std::enable_if_t<is_player_burn<T>::value, Action*> play_burn(Game* g, Player* p, Card* c) {
    return static_cast<T*>(c)->cast_from_hand(g->other_player(p));
}
template<class T>
std::enable_if_t<is_global_burn<T>::value, Action*> play_burn(Game* g, Player* p, Card* c) {
    return static_cast<T*>(c)->cast_from_hand();
}

template<> struct is_player_burn<LavaAxe> : std::true_type{};
template<> struct is_player_burn<LavaSpike> : std::true_type{};
template<> struct is_player_burn<LightningBolt> : std::true_type{};
template<> struct is_player_burn<Shock> : std::true_type{};
template<> struct is_player_burn<VolcanicHammer> : std::true_type{};

template<> struct is_global_burn<VolcanicFallout> : std::true_type{};
template<> struct is_global_burn<AngerOfTheGods> : std::true_type{};

std::unordered_map<std::string, BurnRecognizer::play_burn_t> BurnRecognizer::playmap =
{
	{ "lavaaxe", play_burn < LavaAxe > },
    { "lavaspike", play_burn < LavaSpike > },
    { "volcanichammer", play_burn < VolcanicHammer > },
	{ "lightningbolt", play_burn < LightningBolt> },
	{ "shock", play_burn < Shock > },
	{ "volcanicfallout", play_burn < VolcanicFallout > },
    { "angerofthegods", play_burn < AngerOfTheGods > }
};
