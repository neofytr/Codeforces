#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <unordered_map>
#include <vector>
using namespace std;

#define MAX 300005
using ll = long long;

vector<int> graph[MAX];
char letter[MAX];
bool visited[MAX] = {false};
bool path[MAX] = {false};

ll dfs(int node, string &str) {
    visited[node] = true;
    path[node] = true;
    str.push_back(letter[node]);

    if (graph[node].empty()) {
        // end of the path
        ll maxOccur = LLONG_MIN;
        unordered_map<char, ll> mapping;
        for (char c : str) {
            mapping[c]++;
            maxOccur = max(mapping[c], maxOccur);
        }

        path[node] = false;
        str.pop_back();
        return maxOccur;
    }

    ll maximum = LLONG_MIN;
    for (int v : graph[node]) {
        if (!visited[v]) {
            ll result = dfs(v, str);
            if (result == -1)
                return -1; // cycle detected down the call
            maximum = max(result, maximum);
        } else if (path[v]) {
            // cycle detected
            return -1;
        }
    }

    path[node] = false;
    str.pop_back();
    return maximum;
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int node = 1; node <= n; node++) {
        cin >> letter[node];
    }

    int a, b;
    while (m--) {
        cin >> a >> b; // a -> b
        if (a == b)
            continue;
        graph[a].push_back(b);
    }

    ll maximum = LLONG_MIN;
    for (int node = 1; node <= n; node++) {
        if (!visited[node]) {
            string str;
            memset((void *)path, 0, (n + 1) * sizeof(bool));
            ll result = dfs(node, str);
            if (result == -1) {
                cout << -1 << endl;
                return EXIT_SUCCESS;
            }
            maximum = max(maximum, result);
        }
    }

    cout << maximum << endl;
    return EXIT_SUCCESS;
}
