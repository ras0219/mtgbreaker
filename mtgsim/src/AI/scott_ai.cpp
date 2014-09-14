#include "card.hpp"
#include "AI/ai.hpp"

struct ScottAILogic : PlayerLogicMixin<ScottAILogic> {
	Action* precombat_main(Game* g, Player* p) {
		if (g->active_player != p) return nullptr;
		
		if (can_play_land(g, p)) {
			auto lands = find_lands(p);
			if (lands.size() > 0)
			{
				auto c = lands.front();
				std::cerr << p->name << " plays " << c->name << std::endl;
				return play_land(c);
			}
		}

		// Find the strongest creature that I have the mana to play.
        auto strongest_creature = [p](const Card* a, const Card* b)
		{
			return a->power < b->power;
		};
		auto c = find_playable_creature_with_attributes(g, p, strongest_creature);

		// If I have a creature I can play, play it!
		if (c != nullptr)
		{
			// Tap lands required to play the creature.
			tap_required_lands(g, p, c);

			std::cerr << p->name << " plays " << c->name << std::endl;
			return play_creature(p, c);
		}

		return nullptr;
	}
    std::vector<Permanent*> attack(Game* g, Player* p) {
		std::vector<Permanent*> creatures_to_attack_with;

		// Find all my creatures and attack with them.
		for (auto c : g->battlefield) {
			if (c->controller != p) continue;
			if (c->can_attack(g, p) != nullptr) continue;
			std::cerr << p->name << " attacks with " << c->card->name << std::endl;
			creatures_to_attack_with.push_back(c);
		}

		return creatures_to_attack_with;
	}
};

PlayerLogic* make_scotts_ai() {
	return new ScottAILogic();
}
