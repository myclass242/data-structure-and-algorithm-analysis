#include "buttle.h"

#define DATA_NUMBER 100

int main(int argc, char *argv)
{
    Link buttle1[DIGIT_NUMBER];
    Link buttle2[DIGIT_NUMBER];
    ButtleInit(buttle1);
    ButtleInit(buttle2);

    //int data[DATA_NUMBER];
    for (int k = 0; k < DATA_NUMBER; ++k)
    {
        //data[k] = k;
        ButtleInsertData(buttle1, k, DIGIT_NUMBER);
    }
    ButtleSort(buttle1, buttle2, DIGIT_NUMBER * NUMBER_SYSTEM);
    return 0;
   
}
