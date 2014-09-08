#pragma once

#include <array>
#include <algorithm>
#include <iostream>


struct ManaPool
{
    ManaPool() : pool() {}
    ManaPool(std::array<unsigned int, 6> const& arr) : pool(arr) {}

    enum Type
    {
        COLORLESS,
        GREEN,
        BLACK,
        BLUE,
        WHITE,
        RED
    };
    std::array<unsigned int, 6> pool;

    unsigned int& operator[](Type sz) {
        return pool[sz];
    }

    unsigned int operator[](Type sz) const {
        return pool[sz];
    }

    bool operator>=(ManaPool const& o);
    ManaPool& operator-=(ManaPool const& o);

    static ManaPool parse(const char* cost);
};

std::ostream& operator<<(std::ostream& os, const ManaPool& mp); 

inline ManaPool& operator +=(ManaPool& m, ManaPool::Type t)
{
    m[t]++;
    return m;
}

namespace impl
{
    template<unsigned int R, unsigned int G, unsigned int B, unsigned int W, unsigned int U, unsigned int C>
    struct StaticManaPoolHelper
    {
        static const ManaPool value;
    };

    template<unsigned int R, unsigned int G, unsigned int B, unsigned int W, unsigned int U, unsigned int C>
    const ManaPool StaticManaPoolHelper<R,G,B,W,U,C>::value = { { C, G, B, U, W, R } };

    template<class MPH, ManaPool::Type...Ts>
    struct StaticManaPoolImpl;

    template<unsigned int R, unsigned int G, unsigned int B, unsigned int W, unsigned int U, unsigned int C, ManaPool::Type...Ts>
    struct StaticManaPoolImpl<StaticManaPoolHelper<R, G, B, W, U, C>, ManaPool::RED, Ts...>
        : StaticManaPoolImpl<StaticManaPoolHelper<R+1, G, B, W, U, C>, Ts...>
    {};

    template<unsigned int R, unsigned int G, unsigned int B, unsigned int W, unsigned int U, unsigned int C, ManaPool::Type...Ts>
    struct StaticManaPoolImpl<StaticManaPoolHelper<R, G, B, W, U, C>, ManaPool::GREEN, Ts...>
        : StaticManaPoolImpl<StaticManaPoolHelper<R, G+1, B, W, U, C>, Ts...>
    {};

    template<unsigned int R, unsigned int G, unsigned int B, unsigned int W, unsigned int U, unsigned int C, ManaPool::Type...Ts>
    struct StaticManaPoolImpl<StaticManaPoolHelper<R, G, B, W, U, C>, ManaPool::BLACK, Ts...>
        : StaticManaPoolImpl<StaticManaPoolHelper<R, G, B+1, W, U, C>, Ts...>
    {};

    template<unsigned int R, unsigned int G, unsigned int B, unsigned int W, unsigned int U, unsigned int C, ManaPool::Type...Ts>
    struct StaticManaPoolImpl<StaticManaPoolHelper<R, G, B, W, U, C>, ManaPool::WHITE, Ts...>
        : StaticManaPoolImpl<StaticManaPoolHelper<R, G, B, W+1, U, C>, Ts...>
    {};

    template<unsigned int R, unsigned int G, unsigned int B, unsigned int W, unsigned int U, unsigned int C, ManaPool::Type...Ts>
    struct StaticManaPoolImpl<StaticManaPoolHelper<R, G, B, W, U, C>, ManaPool::BLUE, Ts...>
        : StaticManaPoolImpl<StaticManaPoolHelper<R, G, B, W, U+1, C>, Ts...>
    {};

    template<unsigned int R, unsigned int G, unsigned int B, unsigned int W, unsigned int U, unsigned int C, ManaPool::Type...Ts>
    struct StaticManaPoolImpl<StaticManaPoolHelper<R, G, B, W, U, C>, ManaPool::COLORLESS, Ts...>
        : StaticManaPoolImpl<StaticManaPoolHelper<R, G, B, W, U, C+1>, Ts...>
    {};

    template<class MPH>
    struct StaticManaPoolImpl < MPH > : MPH
    {};

    using StaticManaPoolHelperBase = StaticManaPoolHelper < 0, 0, 0, 0, 0, 0 > ;
}

template<ManaPool::Type...Ts>
struct StaticManaPool : impl::StaticManaPoolImpl<impl::StaticManaPoolHelperBase, Ts...>
{};

template<ManaPool::Type...Ts>
ManaPool SMP() { return StaticManaPool<Ts...>::value; }