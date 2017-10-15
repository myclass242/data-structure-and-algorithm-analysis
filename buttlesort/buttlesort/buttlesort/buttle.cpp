#include "buttle.h"

static bool OneButtle2Buttles(Link * source, Link * dest, int divisor)
{
    bool sortEnd = true;
    while (!ForwardlistEmpty(source))
    {
        int data = ForwardListTop(source);
        ForwardlistPop(source);
        int destButtleID = (data / (divisor / 10)) % 10;
        if (destButtleID)
        {
            sortEnd = false;
        }
        ForwardlistInsert(&dest[destButtleID], data);
    }
    return sortEnd;
}

void ButtleInit(Link * buttle)
{
    for (int k = 0; k < DIGIT_NUMBER; ++k)
    {
        ForwardlistInit(&buttle[k]);
    }
}

void ButtleInsertData(Link * buttle, int data, int divisor)
{
    int destButtleID = (data / (divisor / 10)) % 10;
    ForwardlistInsert(&buttle[destButtleID], data);
}

static void ButtleCombine(Link *buttles)
{

}

void ButtleSort(Link * source, Link * dest, int divisor)
{
    bool SortEnd = true;
    for (int k = 0; k < DIGIT_NUMBER; ++k)
    {
        if (!OneButtle2Buttles(&source[k], dest, divisor))
        {
            SortEnd = false;
       }
    }

    if(SortEnd)
    { 
        return;
    }
    else
    {
        ButtleSort(dest, source, divisor * NUMBER_SYSTEM);
    }
}
