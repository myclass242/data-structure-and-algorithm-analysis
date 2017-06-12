#include "printdouble.h"
#include "printint.h"
#include<iostream>
#include<utility>

const double EPS=1e-8;

static std::pair<long long,double> SpilitDouble(double d)
{
    /* minus */
    if(d < -EPS)
    {
        double tmp=d;
        while(tmp + 1 < -EPS)
        {
            tmp+=1;
        }
        return {d-tmp,-tmp};
    }
    /* plus */
    else if(d > EPS)
    {
        double tmp=d;
        while(tmp -1 > EPS)
        {
            tmp-=1;
        }
        return {d - tmp,tmp};
    }
    /* 0.0 */
    return {0,0.0};
}

void PrintDouble(double d)
{
    std::pair<long long,double> spilit=SpilitDouble(d);
    PrintInt(spilit.first);
    std::cout<<'.';
    PrintInt(spilit.second*10*10*10*10*10*10);
}

