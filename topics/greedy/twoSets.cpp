// https://cses.fi/problemset/task/1629/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n;
    cin >> n;

    long long sum = (n * (n + 1)) / 2;

    if (sum & 1)
    {
        cout << "NO\n";
        return EXIT_SUCCESS;
    }

    long long target = sum / 2;

    vector<bool> subset(n + 1, 0);
    long long curr = 0;
    long long count = 0;
    for (long long num = 1; num <= n; num++)
    {
        curr += num;
        subset[num] = true;
        if (curr > target)
        {
            long long left = curr - target;
            subset[left] = false;
            break;
        }
        else if (curr < target)
        {
            count++;
        }
        else
        {
            count++;
            break;
        }
    }
    
    cout << "YES" << endl;
    cout << count << endl;
    for (long long num = 1; num <= n; num++)
    {
        if (subset[num])
        {
            cout << num << " ";
        }
    }
    cout << endl;

    cout << n - count << endl;
    for (long long num = 1; num <= n; num++)
    {
        if (!subset[num])
        {
            cout << num << " ";
        }
    }
    cout << endl;

    return EXIT_SUCCESS;
}