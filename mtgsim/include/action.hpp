#pragma once

#include <vector>

struct Game;
struct Player;
struct Card;

struct Action
{
    virtual ~Action() {}
    virtual const char* check(Game* g, Player* p) = 0;
    virtual void enact(Game* g, Player* p) = 0;
};

struct PlayLandAction : Action
{
    PlayLandAction(Card* c) : card(c) {}

    virtual const char* check(Game* g, Player* p);
    virtual void enact(Game* g, Player* p);

    Card* card;
};

struct CastSpell : Action
{
    CastSpell(Card* c, struct Stackable* s, std::vector<Card*> m) : card(c), mana(m) {}

    virtual const char* check(Game* g, Player* p);
    virtual void enact(Game* g, Player* p);

    Card* card;
    struct Stackable* stackable;
    std::vector<Card*> mana;
    std::vector<Card*> other;
};
