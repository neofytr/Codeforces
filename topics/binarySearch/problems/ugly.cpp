// https://leetcode.com/problems/ugly-number-iii/description/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    long long gcd(long long a, long long b)
    {
        return !b ? a : gcd(b, a % b);
    }

    long long lcm(long long a, long long b)
    {
        return a / gcd(a, b) * b;
    }

    long long count(long long x, long long a, long long b, long long c)
    {
        long long ab = lcm(a, b);
        long long bc = lcm(b, c);
        long long ca = lcm(c, a);
        long long abc = lcm(ab, c);

        return x / a + x / b + x / c - x / ab - x / bc - x / ca + x / abc;
    }

    int nthUglyNumber(const int n, const int a, const int b, const int c)
    {

        // we are to find a number x such that count(x) == n
        // so, we find the minimum x such that count(x) >= n

        long long left = 1;
        long long right = 2e18;

        while (left < right)
        {
            long long mid = left + (right - left) / 2;
            if (count(mid, a, b, c) >= n)
                right = mid;
            else
                left = mid + 1;
        }

        return (int)left;
    }
};