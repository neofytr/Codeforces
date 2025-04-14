#include <bits/stdc++.h>
using namespace std;

#define MAX 10000

int main()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<bitset<MAX>> mukul(n + 1);
    vector<bitset<MAX>> suman(m + 1);

    mukul[0] = 0;
    suman[0] = 0;

    int val;
    for (int index = 1; index <= n; index++)
    {
        cin >> val;
        mukul[index] = mukul[index - 1];
        mukul[index][val] = ~mukul[index][val];
    }

    for (int index = 1; index <= n; index++)
    {
        cin >> val;
        suman[index] = suman[index - 1];
        suman[index][val] = ~suman[index][val];
    }

    int l1, r1, l2, r2;

    while (q--)
    {
        cin >> l1 >> r1 >> l2 >> r2;
        cout << ((mukul[r1] ^ mukul[l1 - 1]) ^ (suman[r2] ^ suman[l2 - 1])).count() << endl;
    }

    return EXIT_SUCCESS;
}