#include "game.hpp"

std::vector<Card*>::iterator PlayerLogic::discard(Game* g, Player* p, int diff) {
    return p->hand.end() - diff;
}