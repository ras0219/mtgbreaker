#pragma once

#include <string>
#include <vector>
#include <memory>
#include "mana.hpp"

struct CardInfo
{
    std::string id;
    std::string name;
    std::vector<std::string> attrs;

    /// converted mana cost
    unsigned int cmc;
    /// mana cost
    ManaPool cost;

    unsigned int power;
    unsigned int toughness;

    bool has(const char* attr) const {
        return std::find(attrs.begin(), attrs.end(), attr) != attrs.end();
    }
};

struct CardClass
{
    virtual ~CardClass() { }
    virtual const CardInfo& info() const = 0;
    virtual struct Card* create(struct Player* p) const = 0;
};

template<class C>
struct CardClassImpl : CardClass
{
    virtual const CardInfo& info() const override
    {
        return C::info_data;
    }
    virtual struct Card* create(struct Player* p) const override
    {
        auto c = new C;
        c->owner = p;
        c->controller = p;
        return c;
    }
};

struct Card
{
    Card(Player* p = nullptr) : owner(p), controller(p), tapped(false) {}
    virtual ~Card() {}
    virtual const CardInfo& info() const = 0;
    virtual const CardClass& cardclass() const = 0;

    struct Player* owner;
    struct Player* controller;
    bool tapped;
};

template<class Derived, class Base = Card>
struct CardMixin : Base
{
    virtual const CardInfo& info() const override
    {
        return info_data;
    }
    virtual const CardClass& cardclass() const override
    {
        return cardclass_data;
    }

    static const CardClassImpl<Derived> cardclass_data;
    static const CardInfo info_data;
};

template<class Derived, class Base>
const CardClassImpl<Derived> CardMixin<Derived, Base>::cardclass_data;

struct Deck
{
    std::vector<const CardClass*> cardlist;

    std::vector<Card*> instance(Player* p) const
    {
        std::vector<Card*> cards;
        cards.reserve(cardlist.size());
        for (auto cc : cardlist)
        {
            cards.push_back(cc->create(p));
        }
        return cards;
    }
};

extern std::vector<const CardClass*> GLOBAL_CARD_LIST;

template<class C>
C* card_cast(Card* c) {
    if (c->info().id == C::info_data.id)
        return static_cast<C*>(c);
    else
        throw std::bad_cast("bad card cast");
}