// https://atcoder.jp/contests/abc227/tasks/abc227_d

#include <bits/stdc++.h>
using namespace std;

bool canMake(long long x, vector<long long> &emp, long long k)
{
    // we need to complete x projects in total

    long long total = 0;
    for (long long num : emp)
    {
        // we can take at most min(num, x) employees from this dept to put into
        // min(num, x) projects

        total += min(num, x);
    }

    // see if these total employees are sufficient for completing x projects
    return total >= x * k;
}

int main()
{
    int n, k;
    cin >> n >> k;

    vector<long long> emp(n);
    for (long long &val : emp)
    {
        cin >> val;
    }

    long long left = 0;
    long long right = accumulate(emp.begin(), emp.end(), 0LL) / k + 1;

    while (right != left + 1)
    {
        long long mid = left + (right - left) / 2;
        if (canMake(mid, emp, k))
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