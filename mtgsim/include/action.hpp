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

struct CastSpellAction : Action
{
    CastSpellAction(Card* c, struct Stackable* s) : card(c), stackable(s) {}

    virtual const char* check(Game* g, Player* p);
    virtual void enact(Game* g, Player* p);

    Card* card;
    struct Stackable* stackable;
};
