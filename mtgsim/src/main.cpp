#include "game.hpp"
#include "card.hpp"
#include "creature.hpp"
#include "land.hpp"
#include "core_card_set.hpp"
#include "playerlogic.hpp"
#include "player.hpp"
#include <iostream>

Deck deck1 =
{
    {
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data
    }
};

struct NullPlayer : PlayerLogic {
    virtual Action* next_action(Game* g, Player* p) override
    {
        std::cerr << "P" << (size_t)p << "->next_action(" << g->state << ")" << std::endl;
        return nullptr;
    }

};

struct SimplePlayer : PlayerLogic {
    virtual Action* next_action(Game* g, Player* p) override
    {
        std::cerr << "P" << (size_t)p << "->next_action(" << g->state << ")" << std::endl;
        if (g->state == Game::PRECOMBAT_MAIN && g->active_player == p && g->stack.empty())
        {
            return main(g, p);
        }
        return nullptr;
    }
    Action* main(Game* g, Player* p) {
        if (g->lands_played == 0)
        {
            // Search for lands
            auto it = std::find_if(p->hand.begin(), p->hand.end(), [](Card* c) { return c->info().has("land"); });
            if (it != p->hand.end()) {
                auto c = *it;
                auto& i = c->info();
                if (i.id == "forest") {
                    std::cerr << "P" << (size_t)p << " plays " << i.id << std::endl;
                    return card_cast<Forest>(c)->playland_from_hand();
                }
            }
        }
        return nullptr;
    }
};


std::vector<const CardClass*> GLOBAL_CARD_LIST;

int main() {
    const ManaPool& mp = SMP<ManaPool::GREEN>();

    {
        Card* c = new ChargingBadger();
        for (auto c2 : c->info().cost.pool)
            std::cout << c2 << std::endl;
        std::cout << "..." << std::endl;
    }
    {
        for (auto c2 : ChargingBadger::info_data.cost.pool)
            std::cout << c2 << std::endl;
        std::cout << "..." << std::endl;
    }
    {
        for (auto c2 : CardMixin<ChargingBadger>::info_data.cost.pool)
            std::cout << c2 << std::endl;
        std::cout << "..." << std::endl;
    }
    for (auto c3 : mp.pool)
        std::cout << c3 << std::endl;
    return 1;
#if 0

    GLOBAL_CARD_LIST.push_back(&Forest::cardclass_data);
    GLOBAL_CARD_LIST.push_back(&ChargingBadger::cardclass_data);

    SimplePlayer bp1;
    SimplePlayer bp2;

    Game g(new Player(deck1, &bp1), new Player(deck1, &bp2));

    g.play();
    return 0;
#endif
}
