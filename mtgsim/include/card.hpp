#pragma once

#include <string>
#include <vector>
#include <memory>
#include "mana.hpp"

struct Game;

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
    Card(Player* p = nullptr) : owner(p), controller(p), tapped(false), sick(true), damage(0) {}
    virtual ~Card() {}
    virtual const CardInfo& info() const = 0;
    virtual const CardClass& cardclass() const = 0;

    const char* check_tap(Game* g, Player* p);
    void apply_damage(Game* g, int dmg);

    struct Player* owner;
    struct Player* controller;
    bool tapped;
    bool sick;
    unsigned int damage;
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
    Deck(std::vector<const CardClass*> const& cl) : cardlist(cl) {}

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

template<unsigned int SZ, class C> struct CX {};

namespace details {
    template<class...>
    struct CCHolder;

    template<class...>
    struct StaticDeckImpl;

    template<class...ccs, class C, class...Args>
    struct StaticDeckImpl < CCHolder<ccs...>, C, Args... >
        : StaticDeckImpl < CCHolder<ccs..., C>, Args... >
    {};

    template<class...ccs, unsigned int SZ, class C, class...Args>
    struct StaticDeckImpl < CCHolder<ccs...>, CX<SZ, C>, Args... >
        : StaticDeckImpl < CCHolder<ccs..., C>, CX<SZ-1, C>, Args... >
    {};

    template<class...ccs, class C, class...Args>
    struct StaticDeckImpl < CCHolder<ccs...>, CX<0, C>, Args... >
        : StaticDeckImpl < CCHolder<ccs...>, Args... >
    {};

    template<class...ccs>
    struct StaticDeckImpl < CCHolder<ccs...> > {
        static const Deck value;
    };

    template<class...ccs>
    const Deck StaticDeckImpl < CCHolder<ccs...> >::value(std::vector<const CardClass*>{ &ccs::cardclass_data... });
}

template<class...Args>
struct StaticDeck : details::StaticDeckImpl<details::CCHolder<>, Args...> {};


extern std::vector<const CardClass*> GLOBAL_CARD_LIST;

template<class C>
C* card_cast(Card* c) {
    if (c->info().id == C::info_data.id)
        return static_cast<C*>(c);
    else
        throw std::bad_cast("bad card cast");
}