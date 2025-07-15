#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int leastInterval(vector<char> &tasks, int n) {
        vector<int> freq(26, 0);
        for (char t : tasks)
            freq[t - 'A']++;

        priority_queue<int> pq;
        for (int f : freq) {
            if (f > 0) pq.push(f);
        }

        int intervals = 0;

        while (!pq.empty()) {
            int cycle = n + 1;
            vector<int> temp;

            while (cycle-- && !pq.empty()) {
                int cnt = pq.top(); pq.pop();
                if (--cnt > 0) temp.push_back(cnt);
                intervals++;
            }

            for (int remaining : temp) {
                pq.push(remaining);
            }

            if (!pq.empty()) {
                intervals += cycle + 1; // add idle time
            }
        }

        return intervals;
    }
};
