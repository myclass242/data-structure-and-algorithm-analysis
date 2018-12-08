#include "sorting.h"
#include "test.h"
#include <vector>

int main()
{
    std::vector<int> a = { 34, 8, 64, 51, 32, 21 };
    TestNormalSort(InsertSort, a);
    InsertSort(a.begin(), a.end());

    return 0;
}
