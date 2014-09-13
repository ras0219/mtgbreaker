#pragma once

#include <vector>

struct Game;
struct Player;
struct Card;

struct PlayerLogic
{
    virtual ~PlayerLogic() {}

    /// Select an action to be played.
    /// This is called when player P has priority.
    /// Returning a nullptr will count as "Pass"
    virtual struct Action* next_action(Game* g, Player* p) { return nullptr; }

    /// Reorganize P's hand such that the last n cards can be discarded
    virtual void discard(Game* g, Player* p, int n) { }

    /// Declare attackers
    virtual std::vector<Card*> attack(Game* g, Player* p) { return std::vector<Card*>(); }

    /// Declare blockers
    /// <return>list of (blocker, attacker)</return>
    virtual std::vector<std::pair<Card*, Card*>> block(Game* g, Player* p) { return std::vector<std::pair<Card*, Card*>>(); }

    /// Respond to cards
    virtual struct Response* respond(Game* g, Player* p, struct Choice* ch) { return nullptr; }

    /// Order triggered abilities to go onto the stack
    /// <remark>The triggered abilities vector is found in p->triggered_abilities</remark>
    virtual void order_triggered_abilities(Game* g, Player* p) { }
};

template<class Derived, class Base = PlayerLogic>
struct PlayerLogicMixin : Base
{
    virtual struct Action* next_action(Game* g, Player* p) {
        if (!g->stack.empty()) {
            return self()->in_stack(g, p);
        }

        switch (g->state) {
        case Game::UPKEEP:
            return self()->upkeep(g, p);
        case Game::DRAW:
            return self()->draw(g, p);
        case Game::PRECOMBAT_MAIN:
            return self()->precombat_main(g, p);
        case Game::COMBAT_BEGIN:
            return self()->combat_begin(g, p);
        case Game::ATTACKERS:
            return self()->attackers_phase(g, p);
        case Game::BLOCKERS:
            return self()->blockers_phase(g, p);
        case Game::COMBAT_END:
            return self()->combat_end(g, p);
        case Game::POSTCOMBAT_MAIN:
            return self()->postcombat_main(g, p);
        case Game::END_STEP:
            return self()->end_step(g, p);
        case Game::CLEANUP:
            return self()->cleanup(g, p);
        }
        return nullptr;
    }

    struct Action* in_stack(Game* g, Player* p) { return nullptr; }
    struct Action* upkeep(Game* g, Player* p) { return nullptr; }
    struct Action* draw(Game* g, Player* p) { return nullptr; }
    struct Action* precombat_main(Game* g, Player* p) { return nullptr; }
    struct Action* combat_begin(Game* g, Player* p) { return nullptr; }
    struct Action* attackers_phase(Game* g, Player* p) { return nullptr; }
    struct Action* blockers_phase(Game* g, Player* p) { return nullptr; }
    struct Action* combat_end(Game* g, Player* p) { return nullptr; }
    struct Action* postcombat_main(Game* g, Player* p) { return nullptr; }
    struct Action* end_step(Game* g, Player* p) { return nullptr; }
    struct Action* cleanup(Game* g, Player* p) { return nullptr; }

private:
    Derived* self() { return static_cast<Derived*>(this); }
};