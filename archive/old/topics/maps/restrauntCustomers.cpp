#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long a, b;

    // this map keeps track of changes in the number of people at specific times
    map<long long, long long> timeToPersonChange;

    // process each customer's arrival and departure
    while (n--) {
        cin >> a >> b;
        // one person arrives at time a
        timeToPersonChange[a] += 1;
        // one person leaves at time b
        timeToPersonChange[b] -= 1;
    }

    // count will track the current number of people
    long long count = 0;
    // max will store the maximum number of people seen at any time
    long long max = -1;

    // iterate over all-time points in order
    for (auto change: timeToPersonChange) {
        // update the current count based on the change at this time
        count += change.second;
        if (count > max) {
            max = count;
        }
    }

    cout << max << endl;

    return EXIT_SUCCESS;
}
