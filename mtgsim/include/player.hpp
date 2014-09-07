#pragma once

#include <vector>
#include "mana.hpp"

struct Deck;
struct PlayerLogic;
struct Card;

struct Player
{
    Player(Deck const& deck, PlayerLogic* l);
    void draw(unsigned int n = 1);
    void apply_damage(int dmg);

    std::vector<Card*> library;
    std::vector<Card*> hand;
    std::vector<Card*> graveyard;

    bool loss_pending;
    int life;
    ManaPool mana;

    PlayerLogic* ai;
};
