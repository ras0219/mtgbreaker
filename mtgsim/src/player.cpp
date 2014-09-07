#include "player.hpp"
#include "playerlogic.hpp"
#include "card.hpp"
#include <iostream>

Player::Player(Deck const& d, PlayerLogic* l) : loss_pending(false), life(20), ai(l)
{
    // Create a new library instance
    library = d.instance(this);
    std::random_shuffle(library.begin(), library.end());
    if (library.size() < 7) {
        throw std::runtime_error("Deck must be at least 7 cards.");
    }
    // Move the top 7 cards into the hand
    draw(7);
}

void Player::draw(unsigned int n) {
    std::cerr << "Player " << (size_t)this << " draws: " << n << "/" << library.size() << std::endl;

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
    std::cerr << "P" << (size_t)this << " takes " << dmg << " dmg. [" << life << "]" << std::endl;
}