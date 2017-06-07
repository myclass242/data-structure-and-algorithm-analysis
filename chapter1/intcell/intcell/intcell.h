#ifndef INTCELL_H
#define INTCELL_H
#include<iostream>
class IntCell
{
public:
    explicit IntCell(int val=0):StoreValue{val}
    {
        std::cout<<"construct "<<StoreValue<<std::endl;
    }
    IntCell(const IntCell &rf):StoreValue(rf.StoreValue){}

    inline int read(void) const
    {
        return StoreValue;
    }

    inline void write(int val)
    {
        StoreValue = val;
    }

private:
    int StoreValue;
};

#endif // INTCELL_H
