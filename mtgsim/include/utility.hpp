#pragma once

#include <iostream>

#define CHECK(X)     \
    if (!(X))        \
    {                \
        std::cerr << __FILE__ << ":" << __LINE__ << ": " << #X << std::endl; \
        std::abort(); \
    }

#define STRINGIFY(X) #X

#define CHECK_RETURN(X)     \
    if (!(X))        \
    {                \
        return __FILE__ ":" STRINGIFY(__LINE__) ": " #X; \
    }