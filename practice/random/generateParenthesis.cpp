#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void generate(int l, int r, int n, string &str, set<string> &s) {
        if (l >= n && r >= n) {
            cout << str << endl;
            s.insert(str);
            return;
        }

        if (l < n) {
            str.push_back('(');
            generate(l + 1, r, n, str, s);
            str.pop_back();
        }

        if (r < l) {
            str.push_back(')');
            generate(l, r + 1, n, str, s);
            str.pop_back();
        }
    }
    vector<string> generateParenthesis(int n) {
        set<string> s;
        string str;
        generate(0, 0, n, str, s);
        vector<string> res;
        for (string stng : s)
            res.push_back(stng);
        return res;
    }
};

int main() {
    Solution s;
    s.generateParenthesis(3);
    return 0;
}