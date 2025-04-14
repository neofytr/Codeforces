#include <bits/stdc++.h>
using namespace std;

int main()
{
    size_t n, l, r, x;
    cin >> n >> l >> r >> x;

    vector<size_t> difficulty(n);
    for (size_t &val : difficulty)
    {
        cin >> val;
    }

    size_t sum;
    size_t max;
    size_t min;
    size_t num;
    size_t count = 0;

    for (size_t combination = 0; combination < 1 << n; combination++)
    {
        sum = 0;
        max = 0;
        min = UINT64_MAX;
        num = 0;
        for (size_t test = 0; test < n; test++)
        {
            if ((1 << test) & combination)
            {
                num++;
                sum += difficulty[test];
                if (difficulty[test] > max)
                {
                    max = difficulty[test];
                }

                if (difficulty[test] < min)
                {
                    min = difficulty[test];
                }
            }
        }

        if (num < 2)
        {
            continue;
        }

        if (sum >= l && sum <= r && max - min >= x)
        {
            count++;
        }
    }

    cout << count << endl;
}