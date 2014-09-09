#pragma once

#include <vector>
#include <functional>

struct Card;
struct Game;
struct Player;
struct Action;

bool can_play_land(Game* g, Player* p);

std::vector<Card*> find_lands(Player* p);
Action* play_land(Card*);
void tap_land(Game* g, Player* p, Card* c);

bool can_play_creature(Game* g, Player* p);
bool can_play_specific_creature(Player* p, Card* c);

Card* find_playable_creature_with_attributes(Player* p, std::function<bool(Card*, Card*)> cmp);
Action* play_creature(Card*);

void sort_hand_by_cost(Player* p);