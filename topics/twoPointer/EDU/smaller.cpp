#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    vector<int> b(m);

    for (int &val : a)
    {
        cin >> val;
    }

    for (int &val : b)
    {
        cin >> val;
    }

    // a and b are in sorted order
    // for each 0 <= r < m, we need to find the number of elements of array a
    // that are <= b[r]

    // method 1
    int counter = 0;
    for (int index = 0; index < m; index++)
    {
        while (counter < n && a[counter] <= b[index])
        {
            counter++;
        }

        cout << counter << endl;
    }

    // method 2
    int i = 0, j = 0;

    while (i < n && j < m)
    {
        if (a[i] > b[j])
        {
            j++;
            cout << i << endl;
        }
        else
        {
            // since we want less than or equal to
            // we place a[i] in case of equality
            i++;
        }
    }

    while (j < m)
    {
        cout << i << endl;
        j++;
    }

    return EXIT_SUCCESS;
}