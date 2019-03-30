#include "disjoinset.h"

DisjoinSets::DisjoinSets(int numElements)
    : s(numElements)
{
    for (int i = 0; i < numElements; ++i)
    {
        s[i] = -1;
    }
}

int DisjoinSets::find(int x)
{
    // path compression
    // path compression is completely compatible with union by size
    // path compression is not completely compatible with union by height
    // path compression will change the height of set, but we don't recalculate the height,
    // at this time, the height is the estimate height(names Rank)

    if (s[x] < 0)
    {
        return x;
    }
    return s[x] = find(s[x]);
}

int DisjoinSets::find(int x) const
{
#if 0
    // recursion
    if (s[x] < 0)
    {
        return x;
    }
    return find(s[x]);
#else
    int root = x;
    while (s[root] >= 0) {
        root = s[root];
    }

    return root;
#endif
}

void DisjoinSets::unionSet(int root1, int root2)
{
    // Union two disjoint sets
    // for simplicity, we assume root1 ans root2 are distinct
    // and represent set names
    // root1 is the root of set 1
    // root2 is the root of set 2

#if 0
    // union by size
    if (s[root1] < s[root2])
    {
        s[root1] += s[root2];
        s[root2] = root1;
    }
    else
    {
        s[root2] += s[root1];
        s[root1] = root2;
    }
#else
    // union by height
    if (s[root1] < s[root2])
    {
        s[root2] = root1;
    }
    else
    {
        if (s[root1] == s[root2])
        {
            --s[root1];     // update height if same
        }
        s[root2] = root1;   // make root1 new root
    }
#endif
}
