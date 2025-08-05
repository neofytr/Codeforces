#include <bits/stdc++.h>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// Problem: accountsMerge
// URL: https://leetcode.com/problems/accounts-merge/description/
// Difficulty: medium
// Tags:
// Strategy:

#include <bits/stdc++.h>
using namespace std;

class DSU {
  public:
    vector<int> parent;

    DSU(int n) : parent(n) {
        iota(parent.begin(), parent.end(), 0); // parent[i] = i
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx != ry) {
            parent[ry] = rx;
        }
    }
};

class Solution {
  public:
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts) {
        unordered_map<string, int> emailToId;
        unordered_map<int, string> idToEmail;
        unordered_map<string, string> emailToName;
        int id = 0;

        for (const auto &acc : accounts) {
            string name = acc[0];
            for (int i = 1; i < acc.size(); ++i) {
                string email = acc[i];
                if (!emailToId.count(email)) {
                    emailToId[email] = id;
                    idToEmail[id] = email;
                    id++;
                }
                emailToName[email] = name;
            }
        }

        DSU dsu(id);

        for (const auto &acc : accounts) {
            int firstId = emailToId[acc[1]];
            for (int i = 2; i < acc.size(); ++i) {
                dsu.unite(firstId, emailToId[acc[i]]);
            }
        }

        unordered_map<int, vector<int>> groups;
        for (const auto &[email, eid] : emailToId) {
            int root = dsu.find(eid);
            groups[root].push_back(eid);
        }

        vector<vector<string>> result;
        for (auto &[root, group] : groups) {
            vector<string> emails;
            for (int eid : group)
                emails.push_back(idToEmail[eid]);
            sort(emails.begin(), emails.end());
            emails.insert(emails.begin(), emailToName[emails[0]]);
            result.push_back(emails);
        }

        return result;
    }
};
