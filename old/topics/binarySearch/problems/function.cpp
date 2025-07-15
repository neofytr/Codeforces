#include <iostream>
using namespace std;

long long changes(long long x)
{
    // the ones digit changes once every 1 increment
    // the tens digit changes once every 10 increments
    // the hundreds digit changes once every 100 increments
    // the nth digit changes once every 10^n increments; n >= 0

    // ans = x / 1 + x / 10 + x / 100 + ...

    long long total = 0;
    long long mult = 1;
    while (true)
    {
        if (!(x / mult))
        {
            break;
        }
        else
        {
            total += x / mult;
            mult *= 10;
        }
    }

    return total;
}

void solve()
{
    long long l, r;
    cin >> l >> r;

    cout << changes(r) - changes(l) << endl;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}
