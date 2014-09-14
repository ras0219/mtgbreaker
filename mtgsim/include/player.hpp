#pragma once

#include <vector>

#include "mana.hpp"

struct PlayerLogic;
struct Card;
struct Game;
struct Stackable;
struct Permanent;

struct Player
{
    Player(const std::string name, std::vector<const Card*> deck, PlayerLogic* l);
    void draw(unsigned int n = 1);
    void apply_damage(Game* g, const Card* src, int dmg);
    void apply_damage(Game* g, Permanent* src, int dmg);

	std::string name;
    std::vector<const Card*> library;
    std::vector<const Card*> hand;
    std::vector<const Card*> graveyard;

    bool loss_pending;
    int life;
    ManaPool mana;
	unsigned int cmc();

    PlayerLogic* ai;

    std::vector<Stackable*> triggered_abilities;
};
