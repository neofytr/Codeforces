#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;

    vector<long long> beauties(n);
    for (long long &val : beauties)
    {
        cin >> val;
    }

    long long maxone;
    long long maxtwo;
    long long maxthree;
    long long maximum;

    for (int index = 0; index < n - 2; index++)
    {
        maxone = beauties[index];
        maxtwo = beauties[index + 1];
        maxthree = beauties[index + 2];
        if (!index)
        {
            maximum = maxone + maxtwo + maxthree - 2;
        }
        for (int counter = index + 3; counter < n; counter++)
        {
            if (beauties[counter] > maxone)
            {
                maxone = beauties[counter];
            }
            else if (beauties[counter] > maxtwo)
            {
                maxtwo = beauties[counter];
            }
            else if (beauties[counter] > maxthree)
            {
                maxthree = beauties[counter];
            }

            if (maxone + maxtwo + maxthree - (counter - index) > maximum)
            {
                maximum = maxone + maxtwo + maxthree + index - counter;
            }
        }
    }

    cout << maximum << endl;
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