#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long sum = 0;
    long long val;
    unordered_map<long long, long long> remOccur;
    long long count = 0;
    remOccur[0] = 1; // we can already make remainder 0 by taking no elements in the prefix array (0 sum)
    for (int index = 1; index <= n; index++) {
        cin >> val;
        sum = ((sum + val) % n + n) % n;

        // if this sum could be made by a prefix array upto this point, we would just remove it
        // from the current prefix array and make a sum divisible by n
        if (remOccur.count(sum)) {
            count += remOccur[sum];
        }

        remOccur[sum]++;
    }

    cout << count << endl;
    return EXIT_SUCCESS;
}
