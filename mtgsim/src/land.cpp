#include "land.hpp"
#include "mana.hpp"
#include "utility.hpp"
#include "player.hpp"
#include "permanent.hpp"
#include "core_card_set.hpp"

namespace detail {
    void tap_for_mana_impl(Game* g, Player* p, Permanent* m, ManaPool::Type t)
    {
        auto msg = m->can_tap(g, p);

        if (msg)
            throw std::runtime_error(msg);

        ++p->mana[t];

        m->tap(g, p);
    }
}