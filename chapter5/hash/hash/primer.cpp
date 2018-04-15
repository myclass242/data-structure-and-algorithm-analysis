#include "primer.h"
#include <cmath>

static bool IsPrimer(size_t x)
{
    for (int n = 2; n < std::sqrt(x); ++n)
    {
        if (0 == x % n)
        {
            return false;
        }
    }
    return true;
}

size_t NextPrimer(size_t x)
{
    while (!IsPrimer(x))
    {
        ++x;
    }
    return x;
}
