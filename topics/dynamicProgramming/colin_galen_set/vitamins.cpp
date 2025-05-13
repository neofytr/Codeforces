#include <bits/stdc++.h>
using namespace std;

int solve(const vector<pair<int, string> > &juices, const int index, string &vitamins) {
    // returns -1 if there is no way to get all three vitamins from [0, index]
    // otherwise; returns the minimum total price of juices that Petya has to buy to get all
    // three vitamins

    if (index >= juices.size()) {
        return 0;
    }

    pair<int, string> juice = juices[index];
    // we can either choose this juice or not
}

int main() {
    int n;
    cin >> n;

    vector<pair<int, string> > juices(n); // each juice from 0 to n - 1 will have a price and
    // vitamins it contains

    // print -1 if there is no way to get all three vitamins
    // otherwise; print minimum total price of juices that Petya has to buy to get all three vitamins
}
