#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int isLoggedIn = false;
    int count = 0;
    string s;

    while (n--)
    {
        cin >> s;
        if (s == "login")
        {
            isLoggedIn = true;
        }

        if (s == "private" && !isLoggedIn)
        {
            count++;
        }

        if (s == "logout")
        {
            isLoggedIn = false;
        }
    }

    cout << count << endl;
}