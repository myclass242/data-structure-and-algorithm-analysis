#include<iostream>
#include<vector>
#include<string>
#include<iterator>
#include<algorithm>

using std::vector;
using std::string;
const int ROWS = 4;
const int COLS = 4;

const vector<string> puzzle =
{
    "this",
    "wats",
    "oahg",
    "fgdt"
};
const vector<string> dct =
{
    "this",
    "two",
    "fat",
    "that"
};

int FindWord(vector<string> &fdWords, int x, int y, int direction);

int main(void)
{
    int row = 0;
    int col = 0;
    int direction = 0;
    vector<string> words{};
    for (row = 0; row<ROWS; ++row)
    {
        for (col = 0; col<COLS; ++col)
        {
            for (direction = 0; direction<8; ++direction)
            {
                if (FindWord(words, row, col, direction))
                {
                    for (const auto &str : words)
                    {
                        std::cout << str << std::endl;
                    }
                }
            }
        }
    }
    return 0;
}
/*
*direction:
*           0 left to right
*           1 right to left
*           2 up to down
*           3 down to up
*           4 upper left to buttom right
*           5 buttom right to upper left
*           6 upper right to buttom left
*           7 buttom left to upper right
*
*/
int FindWord(vector<string> &fdWords, int x, int y, int direction)
{
    //fdWords=vector<string>{};
    fdWords.clear();
    string tmp{};
    int ret = 0;
    while (x >= 0 && x < ROWS && y >= 0 && y < COLS)
    {
        tmp.push_back(puzzle[x][y]);
        if (std::find(std::begin(dct), std::end(dct), tmp) != std::end(dct))
        {
            fdWords.push_back(tmp);
            ret = 1;
        }
        switch (direction)
        {
        case 0:     //0 left to right
        {
            ++y;
            break;
        }
        case 1:     //1 right to left
        {
            --y;
            break;
        }
        case 2:     //2 up to down
        {
            ++x;
            break;
        }
        case 3:     //3 down to up
        {
            --x;
            break;
        }
        case 4:     //4 upper left to buttom right
        {
            ++x;
            ++y;
            break;
        }
        case 5:     //5 buttom right to upper left
        {
            --x;
            --y;
            break;
        }
        case 6:     //6 upper right to buttom left
        {
            ++x;
            --y;
            break;
        }
        case 7:     //7 buttom left to upper right
        {
            --x;
            ++y;
            break;
        }
        default:
        {
            std::cout << "Direction error" << std::endl;
            return 0;
        }
        }
    }
    return ret;
}
