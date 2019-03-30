#pragma once
#ifndef DISJOIN_SETS_H_
#define DISJOIN_SETS_H_

#include <vector>

class DisjoinSets {
public:
    explicit DisjoinSets(int numElements);

    int find(int x);
    int find(int x) const;
    void unionSet(int root1, int root2);
private:
    std::vector<int> s;
};

#endif