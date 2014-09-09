#pragma once

#include <vector>

#include "mana.hpp"

struct Deck;
struct PlayerLogic;
struct Card;
struct Game;

struct Player
{
    Player(const std::string name, const Deck& deck, PlayerLogic* l);
    void draw(unsigned int n = 1);
    void apply_damage(Game* g, int dmg);

	std::string name;
    std::vector<Card*> library;
    std::vector<Card*> hand;
    std::vector<Card*> graveyard;

    bool loss_pending;
    int life;
    ManaPool mana;
	unsigned int cmc();

    PlayerLogic* ai;
};
