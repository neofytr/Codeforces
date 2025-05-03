#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int findContentChildren(vector<int> &g, vector<int> &s) {
        const int children = static_cast<int>(g.size());
        const int cookies = static_cast<int>(s.size());

        // we are to assign children cookies; however, each child gets at most one cookie
        // each child has a green factor g[i], which is the minimum size cookie that the child
        // will be content with
        // our goal is to maximize the number of content children and output the maximum number

        sort(s.begin(), s.end());
        sort(g.begin(), g.end());

        int i = 0, j = 0;
        int count = 0;
        while (i < children && j < cookies) {
            if (s[j] >= g[i]) {
                // give this cookie to the child
                count++, i++, j++;
            } else {
                j++;
            }
        }

        return count;
    }
};
