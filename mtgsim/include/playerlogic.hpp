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
};

