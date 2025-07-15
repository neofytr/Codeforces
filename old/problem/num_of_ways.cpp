#include <bits/stdc++.h>
using namespace std;

int solve(int s, int e)
{
    if (s == e)
        return 1;
    if (s > e)
        return 0;

    return solve(s + 1, e) + solve(s + 2, e) + solve(s + 3, e);
}

int main()
{
    int s, e;
    cin >> s >> e;
    cout << solve(s, e) << endl;
    return 0;
}
