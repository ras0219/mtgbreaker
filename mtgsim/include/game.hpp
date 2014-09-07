#pragma once

#include "card.hpp"
#include "mana.hpp"

struct Game;
struct Player;

struct PlayerLogic
{
    virtual ~PlayerLogic() {}
    virtual struct Action* next_action(Game* g, Player* p) { return nullptr; }
    // Partition hand such that cards after the returned iterator are discardable
    virtual std::vector<Card*>::iterator discard(Game* g, Player* p, int diff);
};

struct Player
{
    Player(Deck const& deck, PlayerLogic* l);
    void draw(unsigned int n = 1);

    std::vector<Card*> library;
    std::vector<Card*> hand;
    std::vector<Card*> graveyard;

    bool loss_pending;
    int life;
    ManaPool mana;

    PlayerLogic* ai;
};

struct Game
{
    Game(Player* p1_, Player* p2_) : state(PRECOMBAT_MAIN), turn_number(0), p1(p1_), p2(p2_), active_player(p1), priority(p1), passed_players(0), lands_played(0) {}

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

    inline Player* next_player() { return active_player == p1 ? p2 : p1; }

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

    int turn_number;

    Player* p1;
    Player* p2;
    Player* active_player;
    Player* priority;
    int passed_players;
    int lands_played;

    std::vector<Card*> exile;
    std::vector<Card*> battlefield;
    std::vector<struct Stackable*> stack;
};
