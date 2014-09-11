#include "deck.hpp"
#include "card_class.hpp"

std::vector<Card*> Deck::instance(Player* p) const
{
    std::vector<Card*> cards;
    cards.reserve(cardlist.size());
    for (auto cc : cardlist)
    {
        cards.push_back(cc->create(p));
    }
    return cards;
}