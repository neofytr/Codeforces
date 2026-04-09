#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, m;
    cin >> n >> m;

    vector<long long> a(n);
    vector<long long> b(m);

    for (long long &val : a)
        cin >> val;

    for (long long &val : b)
        cin >> val;

    long long count = 0;
    int i = 0, j = 0;

    while (j < m)
    {
        long long freqB = 0;
        long long elt = b[j];

        while (j < m && b[j] == elt)
        {
            freqB++;
            j++;
        }

        while (i < n && a[i] < elt)
        {
            i++;
        }

        long long freqA = 0;
        while (i < m && a[i] == elt)
        {
            freqA++;
            i++;
        }

        count += freqA * freqB;
    }

    cout << count << endl;
    return 0;
}
