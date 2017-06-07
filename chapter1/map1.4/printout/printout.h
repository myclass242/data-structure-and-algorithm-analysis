#ifndef PRINTOUT_H
#define PRINTOUT_H
#include<iostream>
static void PrintDigit(int n)
{
    std::cout<<n;
}
void PrintOut(int n)
{
/*
    if(n<10)
    {
        PrintDigit(n);
    }
    else
    {
//        int tmp=n/10;
       PrintOut(n/10);
       PrintDigit(n%10);
    }
*/
    if(n>9)
    {
        PrintOut(n/10);
    }
    //PrintDigit(n%10);
    PrintDigit(n-(n/10)*10);
}
#endif // PRINTOUT_H
