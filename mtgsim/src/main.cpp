#include "game.hpp"
#include "card.hpp"
#include "creature.hpp"
#include "land.hpp"
#include "core_card_set.hpp"
#include "playerlogic.hpp"
#include "player.hpp"
#include "trogdor.hpp"
#include <iostream>

Deck deck1 =
{
    {
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &Forest::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data,
        &ChargingBadger::cardclass_data
    }
};

struct NullPlayer : PlayerLogic {
    virtual Action* next_action(Game* g, Player* p) override
    {
        std::cerr << "P" << (size_t)p << "->next_action(" << g->state << ")" << std::endl;
        return nullptr;
    }

};

struct SimplePlayer : PlayerLogic {
    virtual Action* next_action(Game* g, Player* p) override
    {
        std::cerr << "P" << (size_t)p << "->next_action(" << g->state << ")" << std::endl;
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
            auto it = std::find_if(p->hand.begin(), p->hand.end(), [](Card* c) { return c->info().has("land"); });
            if (it != p->hand.end()) {
                auto c = *it;
                auto& i = c->info();
                if (i.id == "forest") {
                    std::cerr << "P" << (size_t)p << " plays " << i.id << std::endl;
                    return card_cast<Forest>(c)->playland_from_hand();
                }
            }
        }
        return nullptr;
    }
};

struct CheatAI : PlayerLogic{
	virtual Action* next_action(Game* g, Player* p) override
	{
		std::cerr << "Hi! I am id " << (size_t)p << " and I am THE WINNAR! *flip table*" << std::endl; 
		g->active_player = (g->p1 == p) ? g->p2 : g->p1;
		throw g->active_player;
		return nullptr;
	}
};

struct ConsoleAI : PlayerLogic{
	virtual Action* next_action(Game* g, Player* p) override
	{
		Player* other_player = ((p == g->p1) ? g->p1 : g->p2);
		std::cout << "You get an action! ";
		std::cout << ((p == g->active_player) ? "active player" : "not active player") << std::endl;
		std::cout << "Other side has " << other_player->hand.size() << " card in hand "
			<< other_player->life << " life " << other_player->mana <<  "RBWUG1 mana" << std::endl;
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
			if (action > i)
			{
				std::cout << "i too large. Try again!" << std::endl;
				continue;
			}
			if (action == i) //show card
			{
				unsigned int sel_card = 0;
				do { std::cin >> sel_card; } while (sel_card < (i - 1));
				Card *cur_card = p->hand.at(sel_card);
				std::cout << i << "." << cur_card->info().name << ", "
					<< cur_card->info().power << "/"
					<< cur_card->info().toughness << ", "
					<< cur_card->info().cmc << std::endl;
				std::cout << "Detailed mana cost:" <<
					cur_card->info().cost.pool << std::endl;
				std::cout << "";
				for (unsigned int i = 0; i = cur_card->info().attrs.size(); i++)
					std::cout << cur_card->info().attrs.at[i] << " ";
				std::cout << std::endl;
				continue;
			}
			else//play a card
			{
				Card *cur_card = p->hand.at(i);
				std::cout << "lol playing cards hard" << std::endl;
				continue;
			}
		} while (action != i);
		return nullptr;
	}
};

std::vector<const CardClass*> GLOBAL_CARD_LIST;

int main() {
    GLOBAL_CARD_LIST.push_back(&Forest::cardclass_data);
    GLOBAL_CARD_LIST.push_back(&ChargingBadger::cardclass_data);

    SimplePlayer bp1;
    PlayerLogic* bp2 = make_trogdor_ai();
    auto& tdeck = make_trogdor_deck();
    //SimplePlayer bp2;
	ConsoleAI bp2;

    Game g(new Player(deck1, &bp1), new Player(tdeck, bp2));

    g.play();
	system("pause");
    return 0;
}
