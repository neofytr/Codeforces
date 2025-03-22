#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int k;
    string num;

    cin >> k >> num;

    if (k == 1)
    {
        // since its not possible to delete and not obtain a not prime
        cout << 1 << endl;
        cout << num << endl;
        return;
    }

    for (int index = 0; index < k; index++)
    {
        if (num[index] == '1' || num[index] == '4' || num[index] == '6' || num[index] == '8' || num[index] == '9')
        {
            cout << 1 << endl;
            cout << num[index] << endl;
            return;
        }

        if (index)
        {
            cout << index + 1 << endl;
            for (int counter = 0; counter <= index; counter++)
            {
                cout << num[counter];
            }
            cout << endl;
            return;
        }
    }

    if (num[0] == '2')
    {
        for (int index = 0; index < k; index++)
        {
            if (num[index] == '1')
            {
                cout << 2 << endl;
                cout << 21 << endl;
                return;
            }

            if (num[index] == '7')
            {
                cout << 2 << endl;
                cout << 27 << endl;
                return;
            }
        }

        // now no 1 and 7 are present
        // 23 isnt possible
        // so there are at least two threes
        // we are done

        cout << 2 << endl;
        cout << 33 << endl;

        return;
    }

    // now only numbers present are 3, 5, and 7
    // if any of them are present atleast two times we are done

    unordered_map<char, int> map;
    for (int index = 0; index < k; index++)
    {
        map[num[index]]++;
    }

    if (map['3'] >= 2)
    {
        cout << 2 << endl;
        cout << 33 << endl;
        return;
    }

    if (map['5'] >= 2)
    {
        cout << 2 << endl;
        cout << 55 << endl;
        return;
    }

    if (map['7'] >= 2)
    {
        cout << 2 << endl;
        cout << 77 << endl;
        return;
    }

    // now only the numbers 3, 5 and 7 are present and at most once;
    // k >= 2

    // the possibilities are 35, 57, 73, 357
    // 73 isnt even possible

    if (k == 2)
    {
        cout << 2 << endl;
        cout << num << endl;
        return;
    }

    // only possibility is 357 now
    cout << 2 << endl;
    cout << 35 << endl;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return EXIT_SUCCESS;
}