#include "game.hpp"
#include "action.hpp"
#include "stackable.hpp"
#include "player.hpp"
#include "playerlogic.hpp"
#include "utility.hpp"
#include <algorithm>
#include <iostream>
#include <cassert>

void Game::play() {
    Player* loser = nullptr;
    try {
        do
        {
            untap();
            upkeep();
            if (turn_number != 0)
                draw();
            premain();
            combegin();
            attack();
            block();
            damage();
            comend();
            postmain();
            endstep();
            cleanup();
            // flip the active player
            active_player = active_player == p1 ? p2 : p1;
            turn_number += 1;
        } while (1);
    } catch (Player* p) {
        loser = p;
    }

    std::cerr << "Player " << (size_t)loser << " loses." << std::endl;
}

void Game::untap() {
    for (auto c : battlefield)
    {
        if (c->owner == active_player)
        {
            c->sick = false;
            c->tapped = false;
        }
    }
}

void Game::upkeep() {
    priority = active_player;
    state = UPKEEP;

    resolve_priority();
}

void Game::draw() {
    active_player->draw();

    priority = active_player;
    state = DRAW;

    resolve_priority();
}

void Game::premain() {
    priority = active_player;
    state = PRECOMBAT_MAIN;

    resolve_priority();
}

void kill_card(Game* g, Card* x) {
    auto& b = g->battlefield;
    auto it = std::find(b.begin(), b.end(), x);
    if (it == b.end()) {
        std::cerr << "WARNING: attempted to kill dead card: " << x->info().id << std::endl;
        return;
    }
    std::swap(b.end() - 1, it);
    b.pop_back();

    x->controller = x->owner;
    x->owner->graveyard.push_back(x);

    std::cerr << "Killed card: " << x->info().id << "[" << (size_t)x << "]" << std::endl;
}

void Game::resolve_priority() {
    for (auto x : pending_death) {
    }
    pending_death.clear();

    passed_players = 0;
    do {
        while (passed_players != 2)
        {
            if (priority->loss_pending)
            {
                throw priority;
            }

            auto p = priority;
            Action* a = p->ai->next_action(this, p);
            if (a == nullptr)
            {
                // passed
                ++passed_players;
                priority = priority == p1 ? p2 : p1;
                continue;
            }
            auto check_res = a->check(this, p);
            if (check_res != nullptr)
            {
                std::cerr << "Someone messed up: " << check_res << std::endl;
                throw std::runtime_error(check_res);
            }
            a->enact(this, p);
            passed_players = 0;
        }

        if (stack.size() > 0)
        {
            auto s = stack.back();
            stack.pop_back();
            s->resolve(this);
            delete s;
        }
    } while (stack.size() > 0);
}

void Game::combegin() {
    priority = active_player;
    state = COMBAT_BEGIN;

    resolve_priority();
}

const char* valid_attacker(Game* g, Card* c) {
    CHECK_RETURN(c);
    CHECK_RETURN(c->controller == g->active_player);
    CHECK_RETURN(!c->tapped);
    CHECK_RETURN(!c->sick);
    auto& b = g->battlefield;
    CHECK_RETURN(b.end() != std::find(b.begin(), b.end(), c));
    return nullptr;
}

const char* valid_blocker(Game* g, Card* def, Card* atk) {
    CHECK_RETURN(def->controller != g->active_player);
    CHECK_RETURN(!def->tapped);
    auto& b = g->battlefield;
    CHECK_RETURN(b.end() != std::find(b.begin(), b.end(), def));
    return nullptr;
}

void Game::attack() {
    priority = active_player;
    state = ATTACKERS;

    auto attackers = active_player->ai->attack(this, active_player);
    // Check cards for attackability
    for (auto a : attackers) {
        auto check_res = valid_attacker(this, a);
        if (check_res != nullptr)
        {
            std::cerr << "Someone messed up: " << check_res << std::endl;
            throw std::runtime_error(check_res);
        }
    }
    // Tap all attackers
    for (auto a : attackers) {
        a->tapped = true;
    }

    // Create the attacker array
    atk_blk.clear();
    atk_blk.reserve(attackers.size());
    for (auto a : attackers) {
        atk_blk.emplace_back(a, nullptr);
    }
}

void apply_damage(Game* g, Card* c, int dmg) {
    c->damage += dmg;
    if (c->damage >= c->info().toughness)
        g->pending_death.push_back(c);
}

void Game::block() {
    priority = active_player;
    state = BLOCKERS;

    auto passive_player = active_player == p1 ? p2 : p1;
    auto defenders = passive_player->ai->block(this, passive_player);
    // Check cards for blockability
    for (auto a : defenders) {
        // check if defender can block attacker
        auto check_res = valid_blocker(this, a.first, a.second);
        if (check_res != nullptr)
        {
            std::cerr << "Someone messed up: " << check_res << std::endl;
            throw std::runtime_error(check_res);
        }
        auto it = std::find(atk_blk.begin(), atk_blk.end(), std::pair < Card*, Card* > { a.second, nullptr });
        if (atk_blk.end() == it)
        {
            auto msg = "Attempted to block attacker who isn't attacking (or blocked multiple times)";
            std::cerr << msg << std::endl;
            throw std::runtime_error(msg);
        }
        // it != end
        it->second = a.first;
    }
    // TODO: Declare damage assignment order (509.2)
    // Priority
    resolve_priority();
}
void Game::damage() {
    priority = active_player;
    state = DAMAGE;

    for (auto a : atk_blk) {
        if (a.second != nullptr) {
            // There is a blocker. ROUND 1! Fight!
            apply_damage(this, a.first, a.second->info().power);
            apply_damage(this, a.second, a.first->info().power);
        } else {
            // There isn't a blocker. Hurt 'em plenty.
            auto passive_player = active_player == p1 ? p2 : p1;
            passive_player->apply_damage(a.first->info().power);
        }
    }

    // Priority
    resolve_priority();
}
void Game::comend() {
    priority = active_player;
    state = COMBAT_END;

    // Priority
    resolve_priority();
}
void Game::postmain() {
    priority = active_player;
    state = POSTCOMBAT_MAIN;

    // Priority
    resolve_priority();
}
void Game::endstep() {
    priority = active_player;
    state = END_STEP;

    // Priority
    resolve_priority();
}
void Game::cleanup() {
    auto p = active_player;
    int diff = p->hand.size() - 7;
    if (diff > 0)
    {
        std::cerr << "P" << (size_t)p << " is forced to discard." << std::endl;
        // Give player a chance to choose
        p->ai->discard(this, p, diff);
        assert(p->hand.size() >= (size_t)diff);
        p->hand.erase(p->hand.end() - diff, p->hand.end());
    }

    for (auto c : battlefield)
        c->damage = 0;
}
