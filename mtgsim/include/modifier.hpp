#pragma once

enum ternary {
    PASS,
    NO,
    YES
};

struct Modifier {
    virtual ~Modifier() {}

    virtual ternary has(const char* attr) const;
};
