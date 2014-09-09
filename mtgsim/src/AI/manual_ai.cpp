
#include "AI/ai.hpp"

struct ManualAI : PlayerLogic{

	virtual Action* next_action(Game* g, Player* p) override
	{
		Player* other_player = ((p == g->p1) ? g->p1 : g->p2);
		std::cout << "You get an action! ";
		std::cout << ((p == g->active_player) ? "active player" : "not active player") << std::endl;
		std::cout << "Other side has " << other_player->hand.size() << " card in hand "
			<< other_player->life << " life " << other_player->mana << std::endl;
		return main(g, p);


	}
	Action* main(Game* g, Player* p) {
		std::cout << "Your hands contain: " << std::endl;
		std::cout << "Card Name, Atk/HP, Total Mana" << std::endl;
		unsigned int i = 0;

		for (i = 0; i < p->hand.size(); i++)
		{
			Card *cur_card = p->hand.at(i);
			std::cout << i << "." << cur_card->info().name << ", "
				<< cur_card->info().power << "/"
				<< cur_card->info().toughness << ", "
				<< cur_card->info().cmc << std::endl;
		}
		std::cout << i++ << "." << "Print info on card" << std::endl;
		std::cout << i << "." << "Pass" << std::endl;
		unsigned int action;

		do{
			std::cout << "Select action! Type numberrrrr" << std::endl;
			std::cin >> action;
			if (action > i+2)
			{
				std::cout << "i too large. Try again!" << std::endl;
				continue;
			}
			if (action == i-1) //show card
			{
				unsigned int sel_card = 0;
				do { std::cout << "enter number of card" << std::endl; std::cin >> sel_card; } while (sel_card > (i - 1));
				Card *cur_card = p->hand.at(sel_card);
				std::cout << cur_card->info().name << ", "
					<< cur_card->info().power << "/"
					<< cur_card->info().toughness << ", "
					<< cur_card->info().cmc << std::endl;
				std::cout << "Detailed mana cost:" <<
					cur_card->info().cost.pool << std::endl;
				std::cout << "";
				for (unsigned int i = 0; i < cur_card->info().attrs.size(); i++)
					std::cout << cur_card->info().attrs.at(i) << " ";
				std::cout << std::endl;
				continue;
			}
			else//play a card
			{
				Card *cur_card = p->hand.at(action);
				std::cout << "lol playing cards hard" << std::endl;
				continue;
			}
		} while (action != i+1); //pass action
		return nullptr;
	}
};


PlayerLogic* make_manual_ai() { return new ManualAI(); }
