#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    string str(n, '0');

    if (n & 1)
    {
        for (int index = 0; index < n; index++)
        {
            if (index == n / 2)
            {
                str[index] = '=';
            }
            else
            {
                str[index] = '-';
            }
        }
    }
    else
    {
        for (int index = 0; index < n; index++)
        {
            if (index == n / 2 || index == n / 2 - 1)
            {
                str[index] = '=';
            }
            else
            {
                str[index] = '-';
            }
        }
    }

    cout << str << endl;
}