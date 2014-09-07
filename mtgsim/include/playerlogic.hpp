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
    virtual std::vector<std::pair<Card*, Card*>> block(Game* g, Player* p, std::vector<Card*> const& attackers) { return std::vector<std::pair<Card*, Card*>>(); }

    /// Respond to cards
    virtual struct Response* respond(Game* g, Player* p, struct Choice* ch) { return nullptr; }
};

