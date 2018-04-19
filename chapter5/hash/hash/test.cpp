#include "test.h"
#include <string>
#include <random>
#include "employee.h"

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

    SeparateChainingHash<Employee> eplHash;
    Employee epl1("zy", "hunan", "110");
    Employee epl2("ly", "jx", "119");
    eplHash.insert(epl1);
    eplHash.insert(epl2);
    std::cout << epl1 << " is contain in eplHash: " << eplHash.contain(epl1) << std::endl;
    eplHash.show();
    eplHash.remove(epl1);
    eplHash.show();
}
