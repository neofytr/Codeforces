#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b)
{
    return (b == 0) ? a : gcd(b, a % b);
}

int lcm(int a, int b)
{
    return (a / gcd(a, b)) * b;
}

bool is_divisible(int n, int m) // checks if m divides n
{
    return (n % m == 0);
}

void solve()
{
    int a, b;
    cin >> a >> b;

    if (b == 1)
    {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;

    // x = a (nearly good)
    // y = a*b*b - a (nearly good)
    // z = a*b*b (good)
    // this ensures x + y = z and only z is good

    long long x = a;
    long long z = (long long)a * b * b;
    long long y = z - x;

    cout << x << " " << y << " " << z << endl;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}