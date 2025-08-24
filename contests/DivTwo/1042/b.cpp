#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

void solve_case() {
    int village_folk_count;
    cin >> village_folk_count;
    vector<long long> grump_levels(village_folk_count);
    for (int counter = 0; counter < village_folk_count; ++counter) {
        cin >> grump_levels[counter];
    }

    sort(grump_levels.begin(), grump_levels.end());

    long long total_emeralds = 0;

    if (village_folk_count % 2 != 0) {
        for (int idx = 0; idx < village_folk_count; idx += 2) {
            total_emeralds += grump_levels[idx];
        }
    } else {
        for (int idx = 1; idx < village_folk_count; idx += 2) {
            total_emeralds += grump_levels[idx];
        }
    }

    cout << total_emeralds << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_runs;
    cin >> test_runs;
    while (test_runs--) {
        solve_case();
    }

    return 0;
}