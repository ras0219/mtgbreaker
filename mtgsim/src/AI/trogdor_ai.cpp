#include "AI/ai.hpp"
#include <unordered_map>

struct BurnRecognizer {
    template<class T> static Action* play_burn(Game* g, Player* p, Card* c);

    static bool can_recognize(Card* c) {
        return playmap.find(c->info().id) != playmap.end();
    }

    static Action* recognize(Game* g, Player* p, Card* c) {
        auto it = playmap.find(c->info().id);
        if (it == playmap.end())
            return nullptr;
        else
            return it->second(g, p, c);
    }

    using play_burn_t = Action*(*)(Game*, Player*, Card*);
    static std::unordered_map<std::string, play_burn_t> playmap;
};

template<>
Action* BurnRecognizer::play_burn<LightningBolt>(Game* g, Player* p, Card* c) {
    return card_cast<LightningBolt>(c)->cast_from_hand(g->other_player(p));
}
template<>
Action* BurnRecognizer::play_burn<VolcanicHammer>(Game* g, Player* p, Card* c) {
    return card_cast<VolcanicHammer>(c)->cast_from_hand(g->other_player(p));
}
template<>
Action* BurnRecognizer::play_burn<LavaAxe>(Game* g, Player* p, Card* c) {
    return card_cast<LavaAxe>(c)->cast_from_hand(g->other_player(p));
}
template<>
Action* BurnRecognizer::play_burn<Shock>(Game* g, Player* p, Card* c) {
    return card_cast<Shock>(c)->cast_from_hand(g->other_player(p));
}
template<>
Action* BurnRecognizer::play_burn<VolcanicFallout>(Game* g, Player* p, Card* c) {
    return card_cast<VolcanicFallout>(c)->cast_from_hand();
}

std::unordered_map<std::string, BurnRecognizer::play_burn_t> BurnRecognizer::playmap =
{
    { "lavaaxe", BurnRecognizer::play_burn < LavaAxe > },
    { "volcanichammer", BurnRecognizer::play_burn < VolcanicHammer > },
    { "lightningbolt", BurnRecognizer::play_burn < LightningBolt> },
    { "shock", BurnRecognizer::play_burn < Shock > },
    { "volcanicfallout", BurnRecognizer::play_burn < VolcanicFallout > }
};

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
