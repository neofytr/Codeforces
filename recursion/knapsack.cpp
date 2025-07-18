// https://codeforces.com/group/MWSDmqGsZm/contest/223339/problem/U

#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

int solve(int index, int maxWeight, int currVal, vector<int> &weights, vector<int> &values) {
    int n = (int)weights.size();
    if (!maxWeight)
        return currVal;
    if (maxWeight < 0)
        return INT_MIN;
    if (index >= n) // if we reach the end before exhausing maxWeight, return the current value
        return currVal;

    // we can either choose the element at the current index or not
    int take = solve(index + 1, maxWeight - weights[index], currVal + values[index], weights, values);
    int remove = solve(index + 1, maxWeight, currVal, weights, values);

    return max(take, remove);
}

int main() {
    int n, w;
    cin >> n >> w;

    vector<int> weights(n), values(n);
    for (int index = 0; index < n; index++)
        cin >> weights[index] >> values[index];

    cout << solve(0, w, 0, weights, values) << endl;
    return EXIT_SUCCESS;
}