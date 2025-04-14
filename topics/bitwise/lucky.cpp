#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

long long generateNumber(long long bitset, int totalDigits)
{
    long long result = 0;
    for (int i = 0; i < totalDigits; i++)
    {
        int position = totalDigits - i - 1;

        int digit = ((bitset >> position) & 1) ? 7 : 4;

        result = result * 10 + digit;
    }
    return result;
}

int countSetBits(long long n)
{
    int count = 0;
    while (n)
    {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

long long findNextSuperLucky(long long n)
{
    = if (n <= 47) return 47;

    int digits = 0;
    long long temp = n;
    while (temp > 0)
    {
        digits++;
        temp /= 10;
    }

    for (int length = digits; length <= digits + 2; length += 2)
    {
        int halfLength = length / 2;

        long long bitset = (1LL << halfLength) - 1;

        std::vector<long long> candidates;

        while (bitset < (1LL << length))
        {
            long long superLuckyNumber = generateNumber(bitset, length);
            if (superLuckyNumber >= n)
            {
                candidates.push_back(superLuckyNumber);
            }

            long long c = bitset & -bitset;
            long long r = bitset + c;
            bitset = (((r ^ bitset) >> 2) / c) | r;

            if (bitset >= (1LL << length))
                break;
        }

        if (!candidates.empty())
        {
            return *std::min_element(candidates.begin(), candidates.end());
        }
    }

    return -1;
}

int main()
{
    long long n;
    std::cin >> n;

    long long result = findNextSuperLucky(n);
    std::cout << result << std::endl;

    return 0;
}