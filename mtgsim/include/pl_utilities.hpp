#pragma once

#include <vector>
#include <functional>

struct Card;
struct Game;
struct Player;
struct Action;

bool can_play_land(Game* g, Player* p);

std::vector<const Card*> find_lands(Player* p);
Action* play_land(const Card*);
void tap_land(Game* g, Player* p, const Card* c);
bool tap_required_lands(Game* g, Player* p, const Card* c);

bool can_play_creature(Game* g, Player* p);
bool can_play_specific_creature(Player* p, const Card* c);

const Card* find_playable_creature_with_attributes(Game* g, Player* p, std::function<bool(const Card*, const Card*)> cmp);
Action* play_creature(Player* p, const Card*);

void sort_hand_by_cost(Player* p);