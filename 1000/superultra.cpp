#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool is_composite(int num)
{
    if (num < 4)
        return false;
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
            return true;
    }
    return false;
}

void solve(int n)
{
    vector<int> evens, odds;

    for (int i = 1; i <= n; i++)
    {
        if (i & 1)
            evens.push_back(i);
        else
            odds.push_back(i);
    }

    int chosen_even = -1, chosen_odd = -1;
    for (int even : evens)
    {
        for (int odd : odds)
        {
            if (is_composite(even + odd))
            {
                chosen_even = even;
                chosen_odd = odd;
                break;
            }
        }
        if (chosen_even != -1)
            break;
    }

    if (chosen_even == -1)
    {
        cout << -1 << "\n";
        return;
    }

    for (int x : evens)
    {
        if (x != chosen_even)
            cout << x << " ";
    }

    cout << chosen_even << " " << chosen_odd << " ";

    for (int x : odds)
    {
        if (x != chosen_odd)
            cout << x << " ";
    }

    cout << "\n";
}

int main()
{
    int t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        solve(n);
    }
}
