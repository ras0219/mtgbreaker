
#include "AI/ai.hpp"

struct ScottAILogic : PlayerLogicMixin<ScottAILogic> {
	Action* precombat_main(Game* g, Player* p) {
		return nullptr;
	}
};

PlayerLogic* make_scotts_ai() {
	return new ScottAILogic();
}
