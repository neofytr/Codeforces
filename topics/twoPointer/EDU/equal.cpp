#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<long long> a(n);
    vector<long long> b(m);

    for (long long &val : a)
        cin >> val;

    for (long long &val : b)
        cin >> val;

    // Sort both vectors (if not already sorted)
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int i = 0, j = 0;
    int count = 0;

    while (i < m)
    {
        long long target = b[i];

        int freqB = 0;
        while (i < m && b[i] == target)
        {
            freqB++;
            i++;
        }

        int freqA = 0;
        while (j < n && a[j] < target)
            j++;
        while (j < n && a[j] == target)
        {
            freqA++;
            j++;
        }

        count += freqA * freqB;
    }

    cout << count << endl;

    return 0;
}
