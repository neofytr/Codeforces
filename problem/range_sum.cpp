#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, q;
    cin >> n >> q;

    vector<size_t> prefix(n + 1);
    prefix[0] = 0;

    size_t temp;
    for (int index = 1; index < n + 1; index++)
    {
        cin >> temp;

        prefix[index] = prefix[index - 1] + temp;
    }

    int a, b;
    while (q--)
    {
        cin >> a >> b;
        a--, b--; // since we have one based indexes in the question
        cout << prefix[b + 1] - prefix[a] << "\n";
    }

    return EXIT_SUCCESS;
}