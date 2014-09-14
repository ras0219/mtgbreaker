#pragma once

using Deck = std::vector<const Card*>;

template<unsigned int SZ, class C> struct CX {};

namespace details {
    template<class...>
    struct CCHolder;

    template<class...>
    struct StaticDeckImpl;

    template<class...ccs, class C, class...Args>
    struct StaticDeckImpl < CCHolder<ccs...>, C, Args... >
        : StaticDeckImpl < CCHolder<ccs..., C>, Args... >
    {};

    template<class...ccs, unsigned int SZ, class C, class...Args>
    struct StaticDeckImpl < CCHolder<ccs...>, CX<SZ, C>, Args... >
        : StaticDeckImpl < CCHolder<ccs..., C>, CX<SZ - 1, C>, Args... >
    {};

    template<class...ccs, class C, class...Args>
    struct StaticDeckImpl < CCHolder<ccs...>, CX<0, C>, Args... >
        : StaticDeckImpl < CCHolder<ccs...>, Args... >
    {};

    template<class...ccs>
    struct StaticDeckImpl < CCHolder<ccs...> > {
        static const Deck value;
    };

    template<class...ccs>
    const Deck StaticDeckImpl < CCHolder<ccs...> >::value = { &ccs::instance... };
}

template<class...Args>
struct DeckStatic : details::StaticDeckImpl<details::CCHolder<>, Args...> {};
