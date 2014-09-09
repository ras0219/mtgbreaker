#include "game.hpp"
#include "card.hpp"
#include "creature.hpp"
#include "land.hpp"
#include "core_card_set.hpp"
#include "playerlogic.hpp"
#include "player.hpp"

#include "AI/ai.hpp"
#include "Deck/deck.hpp"

#include <iostream>

int main() {
    Game g(
		new Player(trogdor_deck, make_trogdor_ai()),
		new Player(trogdor_deck, make_trogdor_ai()));

    g.play();

	system("pause");

    return 0;
}
