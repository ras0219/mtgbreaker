#include "AI/ai.hpp"
#include "burnrecognizer.hpp"

struct TrogdorLogic : PlayerLogicMixin<TrogdorLogic> {
    Action* draw(Game* g, Player* p) {
        if (g->active_player != p)
            return nullptr;

        for (auto c : p->hand) {
			std::cerr << p->name << " has " << c->name << std::endl;
        }

        return nullptr;
    }
    Action* precombat_main(Game* g, Player* p) {
        if (g->active_player != p)
            return nullptr;

        if (can_play_land(g, p)) {
            auto lands = find_lands(p);
            if (lands.size() > 0)
                return play_land(lands.front());
        }

        // Find my burns
        std::vector<const Card*> burns;
        for (auto c : p->hand) {
            if (BurnRecognizer::can_recognize(c))
                burns.push_back(c);
        }
        auto num_ez_creatures = std::count_if(g->battlefield.begin(), g->battlefield.end(), [](Permanent* c){
            return c->has_text("creature") && c->toughness() <= 2;
        });
        // Don't use volcanic fallout when there's only 2 creatures out
        if (num_ez_creatures < 3)
            burns.erase(std::remove(burns.begin(), burns.end(), &VolcanicFallout::instance), burns.end());
        if (burns.empty())
            return nullptr;

        // Find my lands
        std::vector<Permanent*> mountains;
        for (auto c : g->battlefield) {
            if (c->controller != p) continue;
            if (c->tapped) continue;
            if (c->card != &Mountain::instance) continue;
            if (c->abilities.front() != &TapForManaAbility<ManaPool::RED>::instance) continue;
            mountains.push_back(c);
        }
        if (mountains.empty())
            return nullptr;

        // Cast the spells that make the people fall down
        for (auto c : burns) {
            auto cmc = c->cmc;
            if (mountains.size() >= cmc) {
                std::for_each(mountains.begin(), mountains.begin() + cmc, [g, p](Permanent* m)
                {
                    TapForManaAbility<ManaPool::RED>::tap_for_mana(g, p, m);
                });
				std::cout << p->name << " casts " << c->name << std::endl;
                return BurnRecognizer::recognize(g, p, c);
            }
        }

        return nullptr;
    }
};

PlayerLogic* make_trogdor_ai() { return new TrogdorLogic(); }
