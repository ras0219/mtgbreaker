#pragma once

#include <iostream>

#define CHECK(X)     \
    if (!(X))        \
    {                \
        std::cerr << __FILE__ << ":" << __LINE__ << ": " << #X << std::endl; \
        std::abort(); \
    }

#define STRINGIFY_EX(X) #X
#define STRINGIFY(X) STRINGIFY_EX(X)

#define CHECK_RETURN(X)     \
    if (!(X))        \
    {                \
        return __FILE__ ":" STRINGIFY(__LINE__) ": " #X; \
    }

template<class...Args> struct IMulti : virtual Args... {};

#if !defined(_MSC_VER)
// Really tho, you guys need to get on that
namespace std {
    template<bool B>
    using enable_if_t = typename ::std::enable_if<B>::type;

    template<class T, class...Args>
    ::std::unique_ptr<T> make_unique(Args&&...args) {
        return ::std::unique_ptr<T>{new T(::std::forward(args)...)};
    }
}
#endif

namespace nstd {
    template<class T, class U>
    bool unstable_erase_first(std::vector<T*>& v, U* t) {
        auto it = std::find(v.begin(), v.end(), t);
        if (it == v.end())
            return false;
        std::iter_swap(it, v.end() - 1);
        v.pop_back();
        return true;
    }
}
