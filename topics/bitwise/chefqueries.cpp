// https://www.codechef.com/problems/CHEFQUE

#include <bits/stdc++.h>
using namespace std;

int main()
{
    size_t q, s, a, b;
    cin >> q >> s >> a >> b;

    bitset<1ULL << 31> set; // initially empty
    uint64_t sum = 0;

    for (size_t i = 0; i < q; i++)
    {
        size_t num = s / 2;

        if (s & 1)
        {
            if (!set[num])
            {
                set[num] = true;
                sum += num;
            }
        }
        else
        {
            if (set[num])
            {
                set[num] = false;
                sum -= num;
            }
        }

        s = (s * a + b) & 0xFFFFFFFFULL; // mask to 2^32
    }

    cout << sum << endl;
    return 0;
}
