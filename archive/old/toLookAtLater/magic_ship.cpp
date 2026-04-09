// https://codeforces.com/problemset/problem/1117/C

#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long x1, y1;
    long long x2, y2;
    int n;
    vector<char> weather(n + 1); // 1-based indexing

    cin >> x1 >> y1;
    cin >> x2 >> y2;
    cin >> n;

    for (int index = 1; index <= n; index++)
    {
        cin >> weather[index];
    }
}