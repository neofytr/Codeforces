#include <bits/stdc++.h>
using namespace std;

#define MAX 100000

int main()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<bitset<MAX + 1>> mukul(n + 1);
    vector<bitset<MAX + 1>> suman(m + 1);

    mukul[0] = 0;
    suman[0] = 0;

    int val;
    for (int index = 1; index <= n; index++)
    {
        cin >> val;
        mukul[index] = mukul[index - 1];
        mukul[index][val] = ~mukul[index - 1][val];
    }

    for (int index = 1; index <= m; index++)
    {
        cin >> val;
        suman[index] = suman[index - 1];
        suman[index][val] = ~suman[index - 1][val];
    }

    int l1, r1, l2, r2;

    // 0 means even number of times. 1 means odd number of times
    bitset<MAX> odd;

    while (q--)
    {
        cin >> l1 >> r1 >> l2 >> r2;
        l1--, r1--, l2--, r2--; // convert to 0-based indexing
        
        

        cout << odd.count() << endl;
        odd = 0;
    }
}