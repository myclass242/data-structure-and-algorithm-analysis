#include"binaryone.h"

int NumsOfBinaryOne(int n)
{
    if(n == 0)
    {
        return 0;
    }
    else if(n == 1)
    {
        return 1;
    }

    if(n%2)
    {
        return NumsOfBinaryOne(n/2) + 1;
        //return NumsOfBinaryOne(n >> 1) +1;
    }
    else
    {
        return NumsOfBinaryOne(n/2);
        //return NumsOfBinaryOne(n >> 1);
    }
}
