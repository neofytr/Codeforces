#include <bits/stdc++.h>
using namespace std;

/*
    problem:
        - given one array 'a' and many arrays 'b1, b2, ..., bk'
        - want to find, for each array bi:
            minDist[i] = min_{x in a, y in bi} |x - y|
        - naive approach:
            for each bi:
                for each x in a:
                    for each y in bi:
                        compute |x - y|
            time complexity: O(k * n * m) -> too slow

    observations:
        - all we need is the nearest element in 'a' to each element in bi
        - if arrays are sorted, we can use two-pointer scan for each bi
        - but if there are many arrays, repeated scanning is expensive

    general efficient method (merged sweep):
        1. merge all arrays into a single array of pairs (value, array_id)
        2. sort the merged array by value
        3. sweep from left to right:
            - maintain the last seen element from 'a'
            - when visiting an element from bi, compute distance to last 'a' element
        4. sweep from right to left:
            - maintain the next element from 'a' on the right
            - update distances to catch the nearest 'a' element on the right
        5. after both sweeps, minDist[i] contains the minimal distance to 'a'
        6. complexity:
            - sorting: O(total_size * log total_size)
            - sweeps: O(total_size)
            - much faster than naive O(k * n * m)
*/

void findMinDistances() {
    int n, k;
    cin >> n >> k; // n = size of array a, k = number of arrays bi

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i]; // read array a

    vector<vector<int>> bi(k);
    int totalSize = n; // start with size of a
    for (int i = 0; i < k; i++) {
        int m; 
        cin >> m; // size of bi
        bi[i].resize(m);
        for (int j = 0; j < m; j++) {
            cin >> bi[i][j];
        }
        totalSize += m; // accumulate total number of elements
    }

    // merge all arrays into one array of (value, array_id)
    vector<pair<int,int>> merged; 
    for (int x : a) merged.push_back({x, -1}); // -1 denotes array 'a'
    for (int i = 0; i < k; i++)
        for (int y : bi[i]) merged.push_back({y, i});

    sort(merged.begin(), merged.end()); // sort by value

    vector<int> minDist(k, INT_MAX); // initialize min distances

    // sweep left -> right
    int lastA = -1e9; // sentinel for last seen element in 'a'
    for (auto &[val, id] : merged) {
        if (id == -1) lastA = val; // update last 'a'
        else minDist[id] = min(minDist[id], val - lastA); // update distance to 'a'
    }

    // sweep right -> left
    lastA = 1e9; // sentinel for next 'a' element
    for (int i = merged.size() - 1; i >= 0; i--) {
        int val = merged[i].first;
        int id = merged[i].second;
        if (id == -1) lastA = val; // update next 'a'
        else minDist[id] = min(minDist[id], lastA - val); // update distance
    }

    // output distances
    for (int i = 0; i < k; i++) cout << minDist[i] << " ";
    cout << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /*
        example input:
            3 2
            1 5 10
            2 4 7
            3 12 15 20
        output:
            minimal distances from 'a' to each bi
    */
    findMinDistances();
}
