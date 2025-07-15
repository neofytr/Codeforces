#include <bits/stdc++.h>
using namespace std;

/*

num &= (num - 1) turns off the last 1 in num (for num > 0)

*/

int countOnes(long long num)
{
    if (!num)
        return 0;

    int count = 0;
    while (true)
    {
        num &= (num - 1);
        count++;
        if (!num)
            return count;
    }

    return 0;
}

int countTrailingZeroes(long long num)
{
    if (!num)
        return sizeof(long long) * 8;

    return countOnes(num - 1) - countOnes(num) + 1;
}

int countLeadingZeroes(long long num)
{
    if (!num)
        return sizeof(long long) * 8;

    while (true)
    {
        if (!(num & (num - 1)))
            return (sizeof(long long) * 8 - countTrailingZeroes(num) - 1);
        else
            num &= (num - 1);
    }

    return 0;
}