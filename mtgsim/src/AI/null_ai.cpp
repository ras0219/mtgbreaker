
#include "AI/ai.hpp"

struct NullPlayer : PlayerLogic {
	virtual Action* next_action(Game* g, Player* p) override
	{
		std::cerr << p->name << "->next_action(" << g->state << ")" << std::endl;
		return nullptr;
	}
};

PlayerLogic* make_null_ai() {
	return new NullPlayer();
}
