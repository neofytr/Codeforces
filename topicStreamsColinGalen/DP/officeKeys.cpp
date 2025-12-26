#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Function to calculate distance: |person - key| + |key - office|
long long get_dist(long long person_loc, long long key_loc, long long office_loc) {
    return abs(person_loc - key_loc) + abs(key_loc - office_loc);
}

// Check if it's possible to match all people within 'time_limit'
bool can_match(long long time_limit, int n, int k, long long p, 
               const vector<long long>& a, const vector<long long>& b) {
    int key_idx = 0;
    int people_matched = 0;

    // Iterate through each person
    for (int i = 0; i < n; i++) {
        // Find the first key that allows this person to reach office in time
        while (key_idx < k) {
            if (get_dist(a[i], b[key_idx], p) <= time_limit) {
                // Found a valid key for this person
                people_matched++;
                key_idx++; // This key is now used
                break; 
            }
            // This key is either too far or invalid for the current person constraints,
            // move to next key. 
            // NOTE: Since we sort, we greedily look for the *first* valid key.
            key_idx++;
        }
    }
    
    // Success if we matched everyone
    return people_matched == n;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    long long p;
    if (!(cin >> n >> k >> p)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<long long> b(k);
    for (int i = 0; i < k; i++) cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    // Binary search for the minimum time
    long long low = 0, high = 2e9 + 7; // Sufficiently large range
    long long ans = high;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (can_match(mid, n, k, p, a, b)) {
            ans = mid;
            high = mid - 1; // Try smaller time
        } else {
            low = mid + 1; // Need more time
        }
    }

    cout << ans << endl;

    return 0;
}