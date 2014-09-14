#include "card.hpp"
#include "AI/ai.hpp"

struct SimplePlayer : PlayerLogic {
	virtual Action* next_action(Game* g, Player* p) override
	{
		std::cerr << p->name << "->next_action(" << g->state << ")" << std::endl;
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
			auto it = std::find_if(p->hand.begin(), p->hand.end(), [](const Card* c) { return c == &Forest::instance; });
			if (it != p->hand.end()) {
				auto c = *it;
				if (c == &Forest::instance) {
                    std::cerr << p->name << " plays a forest" << std::endl;
					return card_cast<Forest>(c)->play();
				}
			}
		}
		return nullptr;
	}
};

PlayerLogic* make_simple_ai() {
	return new SimplePlayer();
}
