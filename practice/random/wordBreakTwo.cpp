#include <bits/stdc++.h>
using namespace std;

void generate(int idx, string &s, set<string> &dict, vector<string> &curr, vector<vector<string>> &res, string word) {
    int n = s.size();
    if (idx == n) {
        if (dict.count(word)) { // last word also must be valid
            curr.push_back(word);
            res.push_back(curr);
            curr.pop_back();
        }
        return;
    }

    // add current character to the ongoing word
    word.push_back(s[idx]);

    // put a space (end word) if valid
    if (dict.count(word)) {
        curr.push_back(word);
        generate(idx + 1, s, dict, curr, res, ""); // start new word
        curr.pop_back();
    }

    // continue adding characters
    generate(idx + 1, s, dict, curr, res, word);
}

vector<vector<string>> wordBreak(string &s, vector<string> &dictionary) {
    set<string> dict(dictionary.begin(), dictionary.end());
    vector<vector<string>> res;
    vector<string> curr;
    generate(0, s, dict, curr, res, "");
    return res;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<string> dict(n);
        for (auto &str : dict)
            cin >> str;

        string s;
        cin >> s;

        vector<vector<string>> res = wordBreak(s, dict);

        for (auto &vec : res) {
            for (int i = 0; i < vec.size(); i++) {
                if (i)
                    cout << " ";
                cout << vec[i];
            }
            cout << endl;
        }
    }
    return 0;
}
