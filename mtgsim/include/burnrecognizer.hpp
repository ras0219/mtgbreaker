#pragma once

#include <unordered_map>

struct Card;
struct Action;
struct Game;
struct Player;

struct BurnRecognizer {
	static bool can_recognize(const Card* c);

	static Action* recognize(Game* g, Player* p, const Card* c);

private:
	using play_burn_t = Action*(*)(Game*, Player*, const Card*);

	static std::unordered_map<const Card*, play_burn_t> playmap;
};


