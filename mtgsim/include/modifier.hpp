#pragma once

struct Game;
struct Card;

enum ternary {
    PASS,
    NO,
    YES
};

struct Modifier {
    virtual void destroyed(Game* g, Permanent* c) { }
    virtual void removed_from_play(Game* g, Permanent* c) { }
    virtual void when_attacks(Game* g, Permanent* c) { }

protected:
    virtual ~Modifier() {}
};

/// 613.1c Layer 3: Text-changing effects are applied. See rule 612, “Text-Changing Effects.”
struct L3Modifier {
    virtual ternary has_text(const char* attr) const { return PASS; }

protected:
    virtual ~L3Modifier() {}
};

/// 613.1f Layer 6: Ability-adding effects, ability-removing effects, and effects that say an object can’t have an ability are applied.
struct L6Modifier {
    virtual ternary has_ability(const char* attr) const { return PASS; }

protected:
    virtual ~L6Modifier() {}
};

/// 613.1g Layer 7: Power- and/or toughness-changing effects are applied.
struct L7Modifier {
    virtual int power(int prev) const { return prev; }
    virtual int toughness(int prev) const { return prev; }

protected:
    virtual ~L7Modifier() {}
};
