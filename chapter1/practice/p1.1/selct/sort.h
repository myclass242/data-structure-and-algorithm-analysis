#ifndef SORT_H
#define SORT_H
#include<functional>
#include<stdbool.h>

/******************************
 *   Bubble Sort
 *****************************/
template<typename T>
void BubbleSort(T &sur,size_t nums)
{
    size_t lookUp=0;
    bool flag=false;
    for(;lookUp<nums-1;++lookUp)
    {
        size_t travelsal=0;
        flag=true;
        for(;travelsal<nums-lookUp-1;++travelsal)
        {
            if(sur[travelsal]>sur[travelsal+1])
            {
                using std::swap;
                swap(sur[travelsal],sur[travelsal+1]);
                flag=false;
            }
        }
        if(flag)
        {
            break;
        }
    }
}

/**********************************
 *  Insert Sort
 * *******************************/
template<typename T>
void InsertSort(T &sur,size_t n)
{
    size_t i=1;
    while(i<n)
    {
        auto key=sur[i];
        long long j=i-1;
        while(sur[j]>key&&j>=0)
        {
            sur[j+1]=sur[j];
            --j;
        }
        sur[j+1]=key;
        ++i;
    }
}
#endif // SORT_H

/*********************************
 *
 * ******************************/
template<typename T>
auto SelectBigN(T &sur,size_t n,size_t nums)
{
    BubbleSort(sur,n);
    //InsertSort(sur,n);
    size_t lookUp=n;
    while(lookUp<nums)
    {
        long long i=n-1;
        auto key=sur[lookUp];
        while(key<sur[i]&&i>=0)
        {
            sur[i+1]=sur[i];
            --i;
        }
        sur[i+1]=key;
        ++lookUp;
    }
    return sur[n];
}
