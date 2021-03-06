#pragma once

#include "card.hpp"
#include "mana.hpp"

struct PlayerLogic;

struct Game
{
    Game(Player* p1_, Player* p2_) : state(PRECOMBAT_MAIN), turn_number(0), p1(p1_), p2(p2_), active_player(p1), passive_player(p2), priority(p1), passed_players(0), lands_played(0) {}

    void play();

    void untap();
    void upkeep();
    void draw();
    void premain();
    void combegin();
    void attack();
    void block();
    void damage();
    void comend();
    void postmain();
    void endstep();
    void cleanup();

    void resolve_priority();

    inline Player* other_player(Player* me) { return me == p1 ? p2 : p1; }

    enum State
    {
        // Beginning
        UNTAP,
        UPKEEP,
        DRAW,
        // Precombat Main
        PRECOMBAT_MAIN,
        // Combat
        COMBAT_BEGIN,
        ATTACKERS,
        BLOCKERS,
        DAMAGE,
        COMBAT_END,
        // Postcombat Main
        POSTCOMBAT_MAIN,
        // Ending
        END_STEP,
        CLEANUP
    } state;

    std::vector<Card*>::iterator find_in_battlefield(const Card* c) {
        return std::find(battlefield.begin(), battlefield.end(), c);
    }
    bool is_in_play(const Card* c) {
        return find_in_battlefield(c) != battlefield.end();
    }
    const char* is_valid_target_creature(Card* c);

    void handle_triggered_abilities(Player* p);

    int turn_number;

    Player* p1;
    Player* p2;

    Player* active_player;
    Player* passive_player;

    Player* priority;
    Player* loser;
    int passed_players;
    int lands_played;

    std::vector<Card*> exile;
    std::vector<Card*> battlefield;
    std::vector<struct Stackable*> stack;

    std::vector<std::pair<Card*, Card*>> atk_blk;
    std::vector<Card*> pending_death;
};
