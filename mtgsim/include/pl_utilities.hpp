#pragma once

#include <vector>

struct Card;
struct Game;
struct Player;
struct Action;

bool can_play_land(Game* g, Player* p);

std::vector<Card*> find_lands(Player* p);
Action* play_land(Card*);

void sort_hand_by_cost(Player* p);