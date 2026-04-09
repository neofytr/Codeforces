// https://codeforces.com/gym/304970/problem/A
#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n;
    cin >> n;

    int pr, root;
    vector<vector<int>> tree(n + 1);
    vector<int> respect(n + 1);
    for (int r = 1; r <= n; r++) {
        cin >> pr >> respect[r];
        if (pr == -1)
            root = r;
        else
            tree[pr].push_back(r); // store directed graph so that we don't have the parent in the adjacency list of a child
    }

    // We have to delete vertices from the tree one by one
    // In each step, we select a vertex r (r != root) such that respect[r] = 1 and respect[c] = 1 for all children c of r
    // If there are a lot of these vertices, we choose the one with the smallest number
    // We then delete this vertex r and attach all of its children to the parent of r
    // We continue this process until we have no such vertices left in the tree

    // We call a vertex v != root removable iff
    // 1. respect[v] = 1
    // 2. respect[c] = 1 for all children c of v

    // If a non-root vertex v is removable initially, it will be removable after a deletion of any other removable vertex
    // Let v and u are removable non-root vertices initially with v != u
    // If there is no edge between v and u, removal of u won't affect the removability of v
    // If there is an edge between u and v, then, either u is the parent of v, or v is the parent of u
    // 1. u is the parent of v
    // In this case, v will be attached to the parent of u and it's removability won't be affected
    // 2. v is the parent of u
    // In this case, the children of u will be attached to v, but since they all have respect == 1 (since u was removable),
    // v will still be removable

    // Also, if a node isn't removable initially, it can't become removable after a deletion

    // Thus, the number of removable nodes is always a constant
    // So, we just print all the removable nodes in sorted order

    vector<int> ans;
    for (int node = 1; node <= n; node++) {
        if (respect[node]) {
            bool pos = true;
            for (const int v : tree[node])
                if (!respect[v]) {
                    pos = false;
                    break;
                }
            if (pos)
                ans.push_back(node);
        }
    }

    if (ans.size() > 0)
        for (const int v : ans)
            cout << v << " ";
    else
        cout << -1;
    cout << endl;
    return EXIT_SUCCESS;
}