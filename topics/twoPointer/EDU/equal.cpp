#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<long long> a(n);
    vector<long long> b(m);

    for (long long &val : a)
    {
        cin >> val;
    }

    for (long long &val : b)
    {
        cin >> val;
    }

    int j = 0;
    int count = 0;
    for (int i = 0; i < m; i++)
    {
        // we find the number of a[j] for which a[j] = b[i]

        while (j < n && a[j] < b[i])
        {
            j++;
        }

        int k = 0;
        while (j + k < n && a[j + k] == b[i])
        {
            k++;
        }

        count += k;
    }

    cout << count << endl;

    return EXIT_SUCCESS;
}