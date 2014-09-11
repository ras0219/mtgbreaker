#pragma once

struct CardInfo;
struct Card;
struct Player;

struct CardClass
{
    virtual ~CardClass() { }
    virtual const CardInfo& info() const = 0;
    virtual Card* create(Player* p) const = 0;
};
