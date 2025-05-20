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

    // a and b are sorted in non-decreasing order
    // we need to merge them into a single array that is sorted in non-decreasing order

    vector<int> c(n + m);

    int i = 0, j = 0, k = 0;
    while (i < n && j < m)
    {
        if (a[i] < b[j])
        {
            c[k++] = a[i++];
        }
        else
        {
            c[k++] = b[j++];
        }
    }

    while (i < n)
    {
        c[k++] = a[i++];
    }

    while (j < m)
    {
        c[k++] = b[j++];
    }

    for (int val : c)
    {
        cout << val << " ";
    }

    cout << endl;
    return EXIT_SUCCESS;
}