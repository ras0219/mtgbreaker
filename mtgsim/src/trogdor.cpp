#include "trogdor.hpp"
#include "playerlogic.hpp"
#include "player.hpp"
#include "pl_utilities.hpp"
#include "core_card_set.hpp"
#include "burn_set.hpp"

struct TrogdorLogic : PlayerLogicMixin<TrogdorLogic> {
    Action* precombat_main(Game* g, Player* p) {
        if (can_play_land(g, p)) {
            auto lands = find_lands(p);
            if (lands.size() > 0)
                return play_land(lands.front());
        }

        std::vector<LightningBolt*> lbs;
        for (auto c : p->hand) {
            if (c->info().id == "lightningbolt")
                lbs.push_back(card_cast<LightningBolt>(c));
        }

        if (!lbs.empty()) {
            if (p->mana[ManaPool::RED] > 0)
                // CAST LIGHTNING BOLT!
                return lbs[0]->cast_from_hand(g->other_player(p));
            // Find some mana, THEN LIGHTNING!
            for (auto c : g->battlefield) {
                if (c->controller != p) continue;
                if (c->tapped) continue;
                if (c->info().id != "mountain") continue;
                // Found a mountain!
                // Gif me mana!
                card_cast<Mountain>(c)->tap_for_mana(g, p);
                // NOW CAST LIGHTNING!
                return lbs[0]->cast_from_hand(g->other_player(p));
            }
        }
        // no lightning ;(

        return nullptr;
    }
};

const Deck trogdor_deck =
{
    {
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data
    }
};

PlayerLogic* make_trogdor_ai() { return new TrogdorLogic(); }
const Deck& make_trogdor_deck() {
    return trogdor_deck;
}