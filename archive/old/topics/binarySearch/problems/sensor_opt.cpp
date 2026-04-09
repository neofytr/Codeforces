// https://atcoder.jp/contests/abc374/tasks/abc374_e

#include <bits/stdc++.h>
using namespace std;

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

        // s <= cap / a[index]

        long long price = LLONG_MAX;
        for (long long s = 0; s <= 1000LL; s++)
        {
            if (s * a[index] > cap)
            {
                break;
            }
            long long rem = cap - s * a[index];
            long long t = (rem + b[index] - 1) / b[index];
            long long cost = s * p[index] + t * q[index];
            price = min(price, cost);
        }

        for (long long s = cap / a[index]; s >= max(0LL, cap / a[index] - 1000LL); s--)
        {
            if (s * a[index] > cap)
            {
                break;
            }
            long long rem = cap - s * a[index];
            long long t = (rem + b[index] - 1) / b[index];
            long long cost = s * p[index] + t * q[index];
            price = min(price, cost);
        }

        // t <= cap / b[index]

        for (long long t = cap / b[index]; t >= max(0LL, cap / b[index] - 1000LL); t--)
        {
            if (t * b[index] > cap)
                break;
            long long rem = cap - t * b[index];
            long long s = (rem + a[index] - 1) / a[index];
            long long cost = s * p[index] + t * q[index];
            price = min(price, cost);
        }

        for (long long t = 0; t <= 1000LL; t++)
        {
            if (t * b[index] > cap)
                break;
            long long rem = cap - t * b[index];
            long long s = (rem + a[index] - 1) / a[index];
            long long cost = s * p[index] + t * q[index];
            price = min(price, cost);
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
    long long right = 1e9 + 1; // maximum production cap of atleast 1e7 + 1 is not achievable

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