#include <bits/stdc++.h>
using namespace std;

#define int long long

#define FAST_IO()                                                                                                                                                                                                                                                                                                                                                                                              \
    ios::sync_with_stdio(false);                                                                                                                                                                                                                                                                                                                                                                               \
    cin.tie(NULL)

/*

num &= (num - 1) turns off the last 1 in num (for num > 0)

*/

int countOnes(long long num) {
    if (!num)
        return 0;

    int count = 0;
    while (true) {
        num &= (num - 1);
        count++;
        if (!num)
            return count;
    }

    return 0;
}

int countTrailingZeroes(long long num) {
    if (!num)
        return sizeof(long long) * 8;

    return countOnes(num - 1) - countOnes(num) + 1;
}

int countLeadingZeroes(long long num) {
    if (!num)
        return sizeof(long long) * 8;

    while (true) {
        if (!(num & (num - 1)))
            return (sizeof(long long) * 8 - countTrailingZeroes(num) - 1);
        else
            num &= (num - 1);
    }

    return 0;
}

// generating the next string in lexicographic order is equivalent to
// adding 1 in base 26
void next(string &str) {
    int n = (int)str.length();
    int r = n - 1;
    while (r >= 0 && str[r] == 'z') // these will generate a carry when 1 is added
        str[r] = 'a', r--;

    if (r >= 0)
        str[r]++; // increment the first non carry generating character
    else
        str = string(n + 1, 'a'); // if everything is a z
}

int32_t main() {
    FAST_IO();

    return 0;
}