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

ManaPool& ManaPool::operator-=(ManaPool const& o)
{
    for (auto color : { GREEN, BLACK, BLUE, WHITE, RED })
    {
        pool[color] -= o[color];
    }
    auto cl = o[COLORLESS];
    for (auto color : { GREEN, BLACK, BLUE, WHITE, RED })
    {
        if (cl > 0) {
            auto x = std::min(pool[color], cl);
            pool[color] -= x;
            cl -= x;
        }
    }
    return *this;
}

ManaPool& ManaPool::operator+=(ManaPool const& o)
{
	for (int x = 0; x < 6; ++x) {
		pool[x] += o.pool[x];
	}
	return *this;
}

bool ManaPool::operator>=(ManaPool const& o) const
{
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

bool ManaPool::operator>(ManaPool const& o) const
{
	auto colorless = pool[COLORLESS];

	for (auto color : { GREEN, BLACK, BLUE, WHITE, RED })
	{
		if (o[color] > pool[color])
		{
			return false;
		}
		else
		{
			colorless += pool[color] - o[color];
		}
	}
	if (o[COLORLESS] >= colorless)
		return false;
	return true;
}

ManaPool operator+(ManaPool const& a, ManaPool const& b)
{
	ManaPool ret;
	ret += a;
	ret += b;
	return ret;
}

std::ostream& operator<<(std::ostream& os, const ManaPool& mp) {
    os << 'C' << mp[ManaPool::COLORLESS];
    os << 'G' << mp[ManaPool::GREEN];
    os << 'B' << mp[ManaPool::BLACK];
    os << 'W' << mp[ManaPool::WHITE];
    os << 'U' << mp[ManaPool::BLUE];
    os << 'R' << mp[ManaPool::RED];
    return os;
}