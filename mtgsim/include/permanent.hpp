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

    void add_mod(Modifier* m) { m_mods.push_back(m); }
    void add_l3(L3Modifier* m) { m_l3.push_back(m); }
    void add_l6(L6Modifier* m) { m_l6.push_back(m); }
    void add_l7(L7Modifier* m) { m_l7.push_back(m); }

    void rem_mod(Modifier* m) { m_mods.erase(std::remove(m_mods.begin(), m_mods.end(), m)); }
    void rem_l3(L3Modifier* m) { m_l3.erase(std::remove(m_l3.begin(), m_l3.end(), m)); }
    void rem_l6(L6Modifier* m) { m_l6.erase(std::remove(m_l6.begin(), m_l6.end(), m)); }
    void rem_l7(L7Modifier* m) { m_l7.erase(std::remove(m_l7.begin(), m_l7.end(), m)); }

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

protected:
    void trigger(Stackable* s);

protected:
    std::vector<struct Modifier*> m_mods;
    std::vector<struct L3Modifier*> m_l3;
    std::vector<struct L6Modifier*> m_l6;
    std::vector<struct L7Modifier*> m_l7;
};
