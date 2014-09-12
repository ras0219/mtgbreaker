#pragma once
#include "AI/ai.hpp"
#include "card_info.hpp"
#include <unordered_map>

struct BurnRecognizer {
	template<class T> static Action* play_burn(Game* g, Player* p, Card* c);

	static bool can_recognize(Card* c);

	static Action* recognize(Game* g, Player* p, Card* c);

	using play_burn_t = Action*(*)(Game*, Player*, Card*);
	static std::unordered_map<std::string, play_burn_t> playmap;
};


