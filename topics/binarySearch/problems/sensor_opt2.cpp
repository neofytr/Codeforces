// https://atcoder.jp/contests/abc374/tasks/abc374_e

#include <bits/stdc++.h>
using namespace std;

long long div_ceil(long long a, long long b)
{
    return (a + b - 1) / b;
}

bool canAchieve(long long cap, long long budget, vector<long long> &a, vector<long long> &p, vector<long long> &b, vector<long long> &q)
{
    // we want to know if we can achieve a production capacity of atleast cap
    // i.e., the minimum of capacities of the processes is at least cap

    for (long long index = 1; index < a.size(); index++)
    {
        // let s be the quantity of machine S
        // let t be the quantity of machine T

        // we want s * a[index] + t * b[index] >= cap
        // the price p = s * p[index] + t * q[index]
        // we want to find a combo (s, t) that minimizes the price p

        long long price = LLONG_MAX;

        for (long long j = 0; j <= 10000LL; j++)
        {
            long long cur = j * p[index];
            long long rem = max(0LL, cap - a[index] * j);
            cur += div_ceil(rem, b[index]) * q[index];
            price = min(price, cur);
        }

        for (long long j = 0; j <= 10000LL; j++)
        {
            long long cur = j * q[index];
            long long rem = max(0LL, cap - b[index] * j);
            cur += div_ceil(rem, a[index]) * p[index];
            price = min(price, cur);
        }

        if (price == LLONG_MAX || budget < price)
            return false;

        budget -= price;
    }

    return true;
}

int main()
{
    long long n, budget;
    cin >> n >> budget;

    vector<long long> a(n + 1);
    vector<long long> p(n + 1);
    vector<long long> b(n + 1);
    vector<long long> q(n + 1);

    for (long long index = 1; index <= n; index++)
    {
        cin >> a[index] >> p[index] >> b[index] >> q[index];
    }

    long long left = 0;        // maximum production cap of atleat 0 is achievable
    long long right = 1e7 + 1; // maximum production cap of atleast 1e7 + 1 is not achievable

    while (right != left + 1)
    {
        long long mid = left + (right - left) / 2;
        if (canAchieve(mid, budget, a, p, b, q))
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }

    cout << left << endl;
    return EXIT_SUCCESS;
}
