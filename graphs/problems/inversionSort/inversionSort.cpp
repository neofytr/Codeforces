#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: inversionSort
// URL: https://www.spoj.com/problems/INVESORT/
// Difficulty: hard
// Tags: 
// Strategy: 

string invert(string &str, int l, int r) {
    string cp = str;
    for (int i = l, j = r; i <= r, j >= l; i++, j--)
        cp[i] = str[j];
    return cp;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string src, dst;
    while(cin >> src >> dst) {
        if (src == "*" && dst == "*")
            break;

         unordered_map<string, bool> mp;
         unordered_map<string, int> dist;
         mp[src] = true;
         dist[src] = 0;
         queue<string> que;
         que.push(src);
         while(!que.empty()) {
            string str = que.front();
            que.pop();

            if (str == dst) {
                cout << dist[str] << endl;
                break;
            }

            for (int len = 2; len <= 10; len++)
                for (int l = 0; l <= 10 - len; l++) {
                    int r = l + len - 1;
                    string nw = invert(str, l, r);
                    if (!mp[nw])
                        mp[nw] = true, dist[nw] = dist[str] + 1, que.push(nw);
                }
         }
    }
    return 0;
}