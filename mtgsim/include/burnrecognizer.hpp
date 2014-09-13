#pragma once

#include <unordered_map>

struct Card;
struct Action;
struct Game;
struct Player;

struct BurnRecognizer {
	static bool can_recognize(Card* c);

	static Action* recognize(Game* g, Player* p, Card* c);

private:
	using play_burn_t = Action*(*)(Game*, Player*, Card*);

	static std::unordered_map<std::string, play_burn_t> playmap;
};


