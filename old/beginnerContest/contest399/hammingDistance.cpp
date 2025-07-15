#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    string s, t;
    cin >> n >> s >> t;

    int count = 0;
    for (int index = 0; index < n; index++)
    {
        if (s[index] != t[index])
        {
            count++;
        }
    }

    cout << count << endl;
}