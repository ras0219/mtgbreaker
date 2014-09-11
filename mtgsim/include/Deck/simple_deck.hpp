#pragma once

#include "deck.hpp"
#include "deck_static.hpp"
#include "core_card_set.hpp"

const Deck simple_deck = DeckStatic <
    CX < 12, Forest >,
    CX < 12, ChargingBadger >
> ::value;
