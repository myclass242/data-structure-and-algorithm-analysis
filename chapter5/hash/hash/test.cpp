#include "test.h"
#include <string>
#include <random>

void TestSeparateChainingHash(void)
{
    SeparateChainingHash<int> scHash;
    std::default_random_engine e;
    std::uniform_int_distribution<int> r(100, 999);
    for (int n = 0; n < 200; ++n)
    {
        scHash.insert(r(e));
    }
    scHash.show();
}
