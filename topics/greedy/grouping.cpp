// https://codeforces.com/problemset/problem/1919/C
#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;

    long long penalty = 0;
    int x = INT_MAX, y = INT_MAX; // x >= y (alway)

    int temp;
    while (n--)
    {
        cin >> temp;

        if (temp <= x)
        {
            x = temp;
        }
        else if (temp > y)
        {
            x = temp;
            swap(x, y);
            penalty++;
        }
        else
        {
            // x < temp <= y
            y = temp;
        }
    }

    cout << penalty << endl;
}

void solveme()
{
    int n;
    cin >> n;

    int penalty = 0;
    int temp;

    int left = INT_MAX, right = INT_MAX;
    while (n--)
    {
        cin >> temp;
        if (left >= temp && right >= temp)
        {
            if (left < right)
            {
                left = temp;
            }
            else
            {
                right = temp;
            }
        }
        else if (left >= temp && right < temp)
        {
            left = temp;
        }
        else if (left < temp && right >= temp)
        {
            right = temp;
        }
        else
        {
            // left < temp && right < temp
            if (left < right)
            {
                left = temp;
            }
            else
            {
                right = temp;
            }

            penalty++;
        }
    }

    cout << penalty << endl;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        solveme();
    }
}