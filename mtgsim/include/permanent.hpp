#pragma once

#include <algorithm>
#include <vector>
#include "modifier.hpp"

struct Game;
struct Player;
struct Card;
struct Stackable;
struct ActivatedAbility;

struct Permanent {
    Permanent(const Card* c, Player* p) : card(c), owner(p), controller(p), tapped(false), sick(true), damage(0) {}
    ~Permanent();

    // State queries
    bool has_text(const char* attr) const;
    int power() const;
    int toughness() const;
    const char* can_tap(Game* g, Player* p) const;
    const char* can_attack(Game* g, Player* p) const;

    // Ability list
    std::vector<const ActivatedAbility*> abilities;

    // State modifiers
    void apply_damage(Game* g, Permanent* src, int dmg);
    void apply_damage(Game* g, const Card* src, int dmg);
    void tap(Game* g, Player* p);
    void untap(Game* g, Player* p);

    template<class T> void add(T*);
    template<class T> void rem(T*);

    // Read only state info
    const Card* card;
    Player* owner;
    Player* controller;
    bool tapped;
    bool sick;
    unsigned int damage;

    template<class F>
    void for_each_mod(F f) {
        for (auto m : m_mods)
            f(m);
        auto it = std::partition(m_mods.begin(), m_mods.end(), [](Modifier* m) { return !m->pending_removal; });
        std::for_each(it, m_mods.end(), [](Modifier* m){ delete m; });
        m_mods.erase(it, m_mods.end());
    }

    void trigger(Stackable* s);

    // Detach is an interface implemented by effects which allows them to be notified when the permanent is to be deleted
    struct Detach {
        virtual ~Detach() {}
        virtual void detach(Permanent*) = 0;
    };

protected:
    std::vector<Modifier*> m_mods;
    std::vector<const L3Modifier*> m_l3;
    std::vector<const L6Modifier*> m_l6;
    std::vector<const L7Modifier*> m_l7;
    std::vector<Detach*> m_ds;
};
