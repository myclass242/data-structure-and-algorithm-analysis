#pragma once
#ifndef EXERCISE_3_4_H_
#define EXERCISE_3_4_H_

namespace zy {
template<typename List>
List Intersection(List &lst1, List &lst2)
{
    List intersectionLst;
    auto lst1Begin = lst1.begin();
    auto lst2Begin = lst2.begin();
    while (lst1Begin != lst1.end() && lst2Begin != lst2.end())
    {
        if (*lst1Begin < *lst2Begin)
        {
            while (lst1Begin != lst1.end()  && *lst1Begin < *lst2Begin)
            {
                ++lst1Begin;
            }
        }
        else if (*lst2Begin < *lst1Begin)
        {
            while (lst2Begin != lst2.end() && *lst2Begin < *lst1Begin)
            {
                ++lst2Begin;
            }
        }
        else
        {
            intersectionLst.push_back(*lst1Begin);
            ++lst1Begin;
            ++lst2Begin;
        }
    }
    return intersectionLst;
}
}

#endif
