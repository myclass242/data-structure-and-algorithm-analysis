#include "printint.h"
#include<iostream>
#include<cstdbool>

static void PrintDigit(int n)
{
    std::cout<<n;
}

static void do_PrintPlusInt(long long n)
{
    if(n>9)
    {
        do_PrintPlusInt(n/10);
    }
    PrintDigit(n%10);
}

void PrintInt(long long n)
{
    if(n<0)
    {
        std::cout<<'-';
        n=-n;
    }
    do_PrintPlusInt(n);
}
