#pragma once

#include "deck.hpp"
#include "deck_static.hpp"
#include "core_card_set.hpp"

const Deck scott_deck = DeckStatic <
	CX < 4, Forest >,
	CX < 4, ChargingBadger >,
	CX < 8, Swamp >/*,
	CX < 4, TyphoidRats >,
	CX < 4, WalkingCorpse >,
	CX < 4, AlloyMyr >*/
> ::value;
