#pragma once
#ifndef EXERCISE_3_5_H_
#define EXERCISE_3_5_H_

namespace zy {
template<typename Lst>
Lst Unionset(Lst &lst1, Lst &lst2)
{
    Lst unionsetLst;
    auto lst1Begin = lst1.begin();
    auto lst2Begin = lst2.begin();
    while (lst1Begin != lst1.end() && lst2Begin != lst2.end())
    {
        if(*lst1Begin < *lst2Begin)
        {
            unionsetLst.push_back(*lst1Begin);
            ++lst1Begin;
        }
        else
        {
            unionsetLst.push_back(*lst2Begin);
            ++lst2Begin;
        }
    }
    while(lst1Begin != lst1.end())
    {
        unionsetLst.push_back(*lst1Begin);
        ++lst1Begin;
    }
    while (lst2Begin != lst2.end())
    {
        unionsetLst.push_back(*lst2Begin);
        ++lst2Begin;
    }
    return unionsetLst;
}
}

#endif
