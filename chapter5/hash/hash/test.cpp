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

void TestQuadraticProbeHash(void)
{
    QuadraticProbeHashTable<int> qpHash;
    std::default_random_engine e1;
    std::uniform_int_distribution<int> r1(100, 999);
    for (int n = 0; n < 200; ++n)
    {
        qpHash.insert(r1(e1));
    }
    std::cout << qpHash << std::endl;

    std::default_random_engine e2;
    std::uniform_int_distribution<int> r2(100, 999);
    for (int n = 0; n < 100; ++n)
    {
        qpHash.remove(r2(e2));
    }
    for (int n = 0; n < 10; ++n)
    {
        int x = r2(e2);
        std::cout << x << " is contain: " << qpHash.contain(x) << std::endl;
    }

    qpHash.makeEmpty();
    std::cout << "Quadratic probe hashtable has " << qpHash.size() << " elements" << std::endl;
}

void TestExercise13(void)
{
    std::string ori = "aoic9faoicfhaww0g\agcoaiocgagcopa\\g-232awgkoajogia";
    std::string target = "aoic9faoicfhaww0g\agcoaiocgagcopa\\g-232awg";
    auto pos = findString(ori, target);
    std::cout << (pos >= 0 ? ori.substr(pos, target.length()) : "-1") << std::endl;
}
