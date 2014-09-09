
#include "AI/ai.hpp"

struct ScottAILogic : PlayerLogicMixin<ScottAILogic> {
	Action* precombat_main(Game* g, Player* p) {
		if (g->active_player != p) return nullptr;
		
		if (can_play_land(g, p)) {
			auto lands = find_lands(p);
			if (lands.size() > 0)
			{
				auto c = lands.front();
				std::cerr << "P" << (size_t)p << " plays " << c->info().id << std::endl;
				return play_land(c);
			}
		}

		// Find the strongest creature that I have the mana to play.
		auto strongest_creature = [p](Card* a, Card* b)
		{
			return a->info().power < b->info().power;
		};
		auto c = find_playable_creature_with_attributes(g, p, strongest_creature);

		// If I have a creature I can play, play it!
		if (c != nullptr)
		{
			// Tap lands required to play the creature.
			tap_required_lands(g, p, c);

			std::cerr << "P" << (size_t)p << " plays " << c->info().id << std::endl;
			return play_creature(c);
		}

		return nullptr;
	}
	std::vector<Card*> attack(Game* g, Player* p) {
		std::vector<Card*> creatures_to_attack_with;

		// Find all my creatures and attack with them.
		for (auto c : g->battlefield) {
			if (c->controller != p) continue;
			if (c->tapped) continue;
			if (!c->info().has("creature")) continue;
			if (c->sick) continue;
			std::cerr << "P" << (size_t)p << " attacks with " << c->info().id << std::endl;
			creatures_to_attack_with.push_back(c);
		}

		return creatures_to_attack_with;
	}
};

PlayerLogic* make_scotts_ai() {
	return new ScottAILogic();
}
