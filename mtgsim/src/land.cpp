#include "land.hpp"
#include "mana.hpp"
#include "utility.hpp"
#include "player.hpp"

void gain_mana(Card* c, ManaPool& mpool) {
    auto& i = c->info();
    if (i.id == "forest")
        mpool[ManaPool::GREEN]++;
    else if (i.id == "plains")
        mpool[ManaPool::WHITE]++;
    else if (i.id == "swamp")
        mpool[ManaPool::BLACK]++;
    else if (i.id == "island")
        mpool[ManaPool::BLUE]++;
    else if (i.id == "mountain")
        mpool[ManaPool::RED]++;
}

void tap_for_mana_impl(Game* g, Player* p, Card* m)
{
    auto msg = m->check_tap(g, p);

    if (msg)
        throw std::runtime_error(msg);

    gain_mana(m, p->mana);

    m->tapped = true;
}