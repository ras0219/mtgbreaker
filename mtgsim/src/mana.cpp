#include "mana.hpp"

ManaPool ManaPool::parse(const char* cost)
{
    ManaPool ret;
    while (*cost != NULL)
    {
        switch (*cost)
        {
        case 'R':
            ret[RED]++;
            break;
        case 'B':
            ret[BLACK]++;
            break;
        case 'W':
            ret[WHITE]++;
            break;
        case 'U':
            ret[BLUE]++;
            break;
        case 'G':
            ret[GREEN]++;
            break;
        case '1':
            ret[COLORLESS]++;
            break;
        default:
            throw std::runtime_error("Not yet implemented");
        }
        ++cost;
    }
    return ret;
}

//Format: RBWUG1. No endl
std::ostream& operator<<(std::ostream& os, const ManaPool& mp)
{
	os << mp.pool[mp.RED] << mp.pool[mp.BLACK] << mp.pool[mp.WHITE] << mp.pool[mp.BLUE] << mp.pool[mp.GREEN] << mp.pool[mp.COLORLESS];
	return os;

}

ManaPool& ManaPool::operator-=(ManaPool const& o)
{
    for (int x = 0; x < 6; ++x) {
        pool[x] -= o.pool[x];
    }
    return *this;
}

bool ManaPool::operator>=(ManaPool const& o) {
    auto colorless = pool[COLORLESS];

    for (auto color : { GREEN, BLACK, BLUE, WHITE, RED })
    {
        if (o[color] > pool[color])
        {
            return false;
        } else
        {
            colorless += pool[color] - o[color];
        }
    }
    if (o[COLORLESS] > colorless)
        return false;
    return true;
}