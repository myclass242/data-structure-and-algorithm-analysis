#include "randomunique.h"
#include <stdlib.h>
#include <time.h>
#include <random>

void RandomUnique1(int * arr, int num)
{
	//srand((unsigned int)time(NULL));
	std::default_random_engine randomEngine((unsigned int)time(NULL));
	std::uniform_int_distribution<int> randomDstb(0, num);
	for (int i = 0; i < num; ++i)
	{
		bool isUniqueNumber = false;
		while (!isUniqueNumber)
		{
			//int randomVar = rand() % num;
			int randomVar = randomDstb(randomEngine);
			randomVar++;                                    /* 值从1开始 */
			isUniqueNumber = true;
			for (int j = 0; j < i; ++j)
			{
				if (randomVar == arr[j])
				{
					isUniqueNumber = false;
					break;
				}
			}
			if (isUniqueNumber)
			{
				arr[i] = randomVar;
				break;
			}
		}
	}
}

void RandomUnique2(int * arr, int num)
{
	/* VS2017不支持C99变长数组标准 */
	//bool used[num] = { false };
	bool *used = (bool *)malloc(sizeof(bool) * num);
	if (!used)
	{
		return;
	}
	for (int i = 0; i < num; ++i)
	{
		used[i] = false;
	}

	//srand((unsigned int)time(NULL));
	std::default_random_engine randomEngine((unsigned int)time(NULL));
	std::uniform_int_distribution<int> randomU(0, num);
	int arrIndex = 0;
	while (arrIndex < num)
	{
		//int randomVar = rand() % num;
		int randomVar = randomU(randomEngine);
		if (!used[randomVar])
		{
			used[randomVar] = true;
			arr[arrIndex] = randomVar + 1;		/* 值从1开始 */
			++arrIndex;
		}
	}
}

static void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void RandomUnique3(int * arr, int num)
{
	for (int i = 0; i < num; ++i)
	{
		arr[i] = i + 1;
	}
	//srand((unsigned int)time(NULL));
	std::default_random_engine randomEngine;
	std::uniform_int_distribution<int> randomU(0, num);
	for (int i = 1; i < num; ++i)
	{
		//int randomIndex = rand() % i;
		int randomIndex = randomU(randomEngine) % i;
		swap(arr + i, arr + randomIndex);
	}
}
