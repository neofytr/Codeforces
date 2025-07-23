#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void bfs(int user, vector<bool> &visitedUser, vector<bool> &visitedGroup, vector<vector<int>> &groupToUser, vector<vector<int>> &userToGroup, vector<int> &component) {
    queue<int> que;
    que.push(user);
    visitedUser[user] = true;

    vector<int> comp;

    while (!que.empty()) {
        int x = que.front();
        comp.push_back(x);
        que.pop();
        for (int gp : userToGroup[x]) {
            if (!visitedGroup[gp]) {
                visitedGroup[gp] = true;
                for (int u : groupToUser[gp]) {
                    if (!visitedUser[u]) {
                        visitedUser[u] = true;
                        que.push(u);
                    }
                }
            }
        }
    }

    for (int user : comp) {
        component[user] = comp.size();
    }
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> userToGroup(n + 1);
    vector<vector<int>> groupToUser(m + 1);

    for (int gp = 1; gp <= m; gp++) {
        int k;
        cin >> k;

        for (int i = 0; i < k; i++) {
            int user;
            cin >> user;
            groupToUser[gp].push_back(user);
            userToGroup[user].push_back(gp);
        }
    }

    // all the users in the same connected component have the same visibility
    vector<bool> visitedUser(n + 1, false);
    vector<bool> visitedGroup(m + 1, false);
    vector<int> component(n + 1, -1);

    for (int user = 1; user <= n; user++) {
        if (!visitedUser[user]) {
            bfs(user, visitedUser, visitedGroup, groupToUser, userToGroup, component);
        }
    }

    for (int user = 1; user <= n; user++) {
        if (component[user] == -1) {
            cout << "1 "; // isolated user
        } else {
            cout << component[user] << " ";
        }
    }
    cout << endl;

    return EXIT_SUCCESS;
}