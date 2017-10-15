#pragma once
#ifndef BUTTLE_H_
#define BUTTLE_H_

#include "forwardlist.h"

#define DIGIT_NUMBER 10
#define NUMBER_SYSTEM DIGIT_NUMBER

void ButtleInit(Link *buttle);

void ButtleInsertData(Link *buttle, int data, int divisor);

void ButtleSort(Link *source, Link *dest, int divisor);

#endif
