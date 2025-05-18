#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    int q;
    cin >> q;
    while (q--)
    {
        ll k;
        cin >> k;

        ll digits = 1;
        ll count = 9;
        ll total = 0;

        // Step 1: Find the digit length
        while (k > total + digits * count)
        {
            total += digits * count;
            digits++;
            count *= 10;
        }

        // Step 2: Find the exact number and digit
        k -= total;                  // now k is offset in this digit range
        ll index = (k - 1) / digits; // which number in this digit length
        ll digit_index = (k - 1) % digits;

        ll start = pow(10, digits - 1);
        ll number = start + index;
        string s = to_string(number);
        cout << s[digit_index] << '\n';
    }
}
