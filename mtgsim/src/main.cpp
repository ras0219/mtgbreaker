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

#define NUM_GAMES 3

int main() {
    int wins = 0;
	for (int x = 0; x < NUM_GAMES; ++x) {
        std::cerr << "============================== GAME START" << std::endl;
		Game g(
			new Player("TROGDOR", trogdor_deck, make_trogdor_ai()),
			new Player("Scott", scott_deck, make_scotts_ai()));

		g.play();
			wins += g.loser == g.p2 ? 1 : 0;
    }
	std::cerr << "Trogdor win %: " << (100.0 * wins / NUM_GAMES) << std::endl;

	system("pause");

    return 0;
}
