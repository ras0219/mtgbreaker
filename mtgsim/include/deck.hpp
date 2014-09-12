#pragma once

#include <vector>

struct CardClass;
struct Card;
struct Player;

struct Deck
{
    Deck(std::vector<const CardClass*> const& cl) : cardlist(cl) {}

    std::vector<Card*> instance(Player* p) const;

private:
    std::vector<const CardClass*> cardlist;
};
