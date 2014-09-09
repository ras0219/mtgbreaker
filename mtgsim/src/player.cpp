#include "player.hpp"
#include "playerlogic.hpp"
#include "card.hpp"
#include <iostream>

Player::Player(const std::string name, const Deck& deck, PlayerLogic* l) : loss_pending(false), life(20), ai(l), name(name)
{
    // Create a new library instance
    library = deck.instance(this);
    std::random_shuffle(library.begin(), library.end());
    if (library.size() < 7) {
        throw std::runtime_error("Deck must be at least 7 cards.");
    }
    // Move the top 7 cards into the hand
    draw(7);
}

void Player::draw(unsigned int n) {
	std::cerr << this->name << " draws: " << n << "/" << library.size() << std::endl;

    if (n > library.size())
    {
        loss_pending = true;
        n = library.size();
    }
    auto it = library.end() - n;
    hand.insert(hand.end(), it, library.end());
    library.erase(it, library.end());
}

void Player::apply_damage(Game* g, int dmg) {
    life -= dmg;
    if (life <= 0)
        loss_pending = true;
	std::cerr << this->name << " takes " << dmg << " dmg. [" << life << "]" << std::endl;
}

unsigned int Player::cmc() {
	return
		mana[ManaPool::BLACK] +
		mana[ManaPool::BLUE] +
		mana[ManaPool::COLORLESS] +
		mana[ManaPool::GREEN] +
		mana[ManaPool::RED] +
		mana[ManaPool::WHITE];
}