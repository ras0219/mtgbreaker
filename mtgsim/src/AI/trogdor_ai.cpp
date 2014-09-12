#include "AI/ai.hpp"
#include "card_info.hpp"
#include "burnrecognizer.hpp"

struct TrogdorLogic : PlayerLogicMixin<TrogdorLogic> {
    Action* draw(Game* g, Player* p) {
        if (g->active_player != p)
            return nullptr;

        for (auto c : p->hand) {
			std::cerr << p->name << " has " << c->info().id << std::endl;
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
        std::vector<Card*> burns;
        for (auto c : p->hand) {
            if (BurnRecognizer::can_recognize(c))
                burns.push_back(c);
        }
        if (burns.empty())
            return nullptr;

        // Find my lands
        std::vector<Mountain*> mountains;
        for (auto c : g->battlefield) {
            if (c->controller != p) continue;
            if (c->tapped) continue;
            if (c->info().id != "mountain") continue;
            mountains.push_back(card_cast<Mountain>(c));
        }
        if (mountains.empty())
            return nullptr;

        // Cast the spells that make the people fall down
        for (auto c : burns) {
            auto cmc = c->info().cmc;
            if (mountains.size() >= cmc) {
                std::for_each(mountains.begin(), mountains.begin() + cmc, [g, p](Mountain* m)
                {
                    m->tap_for_mana(g, p);
                });
				std::cout << p->name << " casts " << c->info().name << std::endl;
                return BurnRecognizer::recognize(g, p, c);
            }
        }

        return nullptr;
    }
};

PlayerLogic* make_trogdor_ai() { return new TrogdorLogic(); }
