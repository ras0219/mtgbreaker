#pragma once

#include <string>
#include <vector>
#include <memory>
#include "mana.hpp"

struct Player;
struct Game;
struct CardInfo;
struct CardClass;

struct Card
{
    Card(Player* p = nullptr) : owner(p), controller(p), tapped(false), sick(true), damage(0) {}
    virtual ~Card() {}
    virtual const CardInfo& info() const = 0;
    virtual const CardClass& cardclass() const = 0;

    // State queries
    bool has(const char* attr) const;

    // State modifiers
    void apply_damage(Game* g, int dmg);

    // Read only state info
    Player* owner;
    Player* controller;
    bool tapped;
    bool sick;
    unsigned int damage;

private:
    std::vector<struct Modifier*> m_mods;
};

const char* can_tap(Game* g, Player* p, Card* c);
extern std::vector<const CardClass*> GLOBAL_CARD_LIST;

template<class C>
C* card_cast(Card* c) {
    if (c->info().id == C::info_data.id)
        return static_cast<C*>(c);
    else
        throw std::bad_cast("bad card cast");
}