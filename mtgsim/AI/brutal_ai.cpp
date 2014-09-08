#include "AI/brutal_ai.hpp"
#include "playerlogic.hpp"
#include "player.hpp"
#include "pl_utilities.hpp"
#include "core_card_set.hpp"

struct BrutalAI : PlayerLogic{
	virtual Action* next_action(Game* g, Player* p) override
	{
		std::cerr << "Hi! I am id " << (size_t)p << " and I am THE WINNAR! *flip table*" << std::endl;
		g->active_player = (g->p1 == p) ? g->p2 : g->p1;
		throw g->active_player;
		return nullptr;
	}
};
