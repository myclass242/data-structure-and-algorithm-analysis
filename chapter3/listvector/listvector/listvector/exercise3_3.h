#pragma once
#ifndef EXERCISE_3_3_H_
#define EXERCISE_3_3_H_
namespace zy {
template<typename Iterator, typename Object>
Iterator Find(Iterator &begin, Iterator &end, const Object item)
{
    while (begin != end)
    {
        if (item == *begin)
        {
            break;
        }
        ++begin;
    }
    return begin;
}
}

#endif
