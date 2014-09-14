#include "burn_set.hpp"
#include "burnrecognizer.hpp"

bool BurnRecognizer::can_recognize(const Card* c) {
	return playmap.find(c) != playmap.end();
}

Action* BurnRecognizer::recognize(Game* g, Player* p, const Card* c) {
	auto it = playmap.find(c);
	if (it == playmap.end())
		return nullptr;
	else
		return it->second(g, p, c);
}

template<class T> struct is_player_burn : std::false_type {};
template<class T> struct is_global_burn : std::false_type {};

template<class T>
std::enable_if_t<is_player_burn<T>::value, Action*> play_burn(Game* g, Player* p, const Card* c) {
    return static_cast<const T*>(c)->cast_from_hand(p, g->other_player(p));
}
template<class T>
std::enable_if_t<is_global_burn<T>::value, Action*> play_burn(Game* g, Player* p, const Card* c) {
    return static_cast<const T*>(c)->cast_from_hand(p);
}

template<> struct is_player_burn<LavaAxe> : std::true_type{};
template<> struct is_player_burn<LavaSpike> : std::true_type{};
template<> struct is_player_burn<LightningBolt> : std::true_type{};
template<> struct is_player_burn<Shock> : std::true_type{};
template<> struct is_player_burn<VolcanicHammer> : std::true_type{};

template<> struct is_global_burn<VolcanicFallout> : std::true_type{};
template<> struct is_global_burn<AngerOfTheGods> : std::true_type{};

#define BURN_PLAYMAP_MACRO(T) { &T::instance, play_burn<T> }

std::unordered_map<const Card*, BurnRecognizer::play_burn_t> BurnRecognizer::playmap =
{
	BURN_PLAYMAP_MACRO(LavaAxe),
    BURN_PLAYMAP_MACRO(LavaSpike),
    BURN_PLAYMAP_MACRO(VolcanicHammer),
    BURN_PLAYMAP_MACRO(LightningBolt),
    BURN_PLAYMAP_MACRO(Shock),
    BURN_PLAYMAP_MACRO(VolcanicFallout),
    BURN_PLAYMAP_MACRO(AngerOfTheGods)
};
