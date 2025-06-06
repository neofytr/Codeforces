// https://codeforces.com/problemset/problem/1097/B

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> angle(n);
    for (int &val : angle)
    {
        cin >> val;
    }

    int sum;

    for (int combination = 0; combination < 1 << n; combination++)
    {
        sum = 0;
        for (int test = 0; test < n; test++)
        {
            if ((1 << test) & combination)
            {
                sum += -angle[test];
            }
            else
            {
                sum += angle[test];
            }
        }

        if (!(sum % 360))
        {
            cout << "YES" << endl;
            return EXIT_SUCCESS;
        }
    }

    cout << "NO" << endl;
    return EXIT_SUCCESS;
}