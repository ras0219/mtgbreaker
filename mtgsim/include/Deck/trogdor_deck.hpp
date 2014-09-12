#pragma once

#include "deck.hpp"
#include "deck_static.hpp"
#include "core_card_set.hpp"
#include "burn_set.hpp"

const Deck trogdor_deck = DeckStatic <
    CX < 16, Mountain >,
    CX < 4, LightningBolt >,
    CX < 4, Shock >,
    CX < 4, VolcanicHammer >,
    CX < 4, LavaSpike >,
    CX < 4, LavaAxe >,
    CX < 4, VolcanicFallout >
> ::value;
