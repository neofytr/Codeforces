#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

// assumes undirected graphs with 0-indexed nodes
class disjointSetUnion {
  public:
    int numNodes;
    int numComp;
    vector<int> parent;
    vector<int> size;

    inline bool checkNode(int x) { return x < numNodes && x >= 0; }
    inline bool checkNodes(int x, int y) { return checkNode(x) && checkNode(y); }
    int getRoot(int x) {
        int y = x;
        while (x != parent[x])
            x = parent[x];

        // path compression
        int temp;
        while (y != parent[y]) {
            temp = parent[y]; // store the parent of the current node
            parent[y] = x;    // make the root node parent of the current node
            y = temp;         // go to the stored parent node
        }
        return x;
    }
    inline int getSize(int x) { return size[getRoot(x)]; }

  public:
    disjointSetUnion(int numNodes) {
        this->numNodes = numNodes;
        parent.resize(numNodes);
        size.resize(numNodes);
        for (int node = 0; node < numNodes; node++) {
            parent[node] = node;
            size[node] = 1; // each node is in it's own connected component
        }
        numComp = numNodes;
        return;
    }

    bool join(int x, int y) { // joins node x and y via an edge if they are not already joined
        if (!checkNodes(x, y))
            return false;

        int rootX = getRoot(x);
        int rootY = getRoot(y);

        if (rootX == rootY) // already in the same component
            return true;

        // x and y are not in the same component
        // they will be after these operations
        // so decrease the component number by 1
        numComp--;
        int sizeX = getSize(x);
        int sizeY = getSize(y);

        if (sizeX > sizeY) {
            swap(sizeX, sizeY);
            swap(rootX, rootY);
        }

        // from here, sizeY >= sizeX always
        // attach X root to Y root
        parent[rootX] = rootY;
        size[rootY] += sizeX;

        return true;
    }

    int isConnected(int x, int y) {
        if (!checkNodes(x, y))
            return -1;

        return getRoot(x) == getRoot(y);
    }

    int componentSize(int x) { return checkNode(x) ? getSize(x) : -1; }
    int numComponents() { return numComp; }
};

// Problem: iceSkating
// URL: https://codeforces.com/problemset/problem/217/A
// Difficulty: medium
// Tags:
// Strategy:

#define MAXCOORD (1000)

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    int x, y;
    disjointSetUnion dsu(n);
    vector<pair<int, int>> pts;
    int r = n;
    while (r--) {
        cin >> x >> y;
        pts.push_back({x, y});
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (pts[i].first == pts[j].first || pts[i].second == pts[j].second) {
                dsu.join(i, j);
            }
        }
    }

    cout << dsu.numComponents() - 1 << endl;
}

/*

int left = 0;
while(s[left] == ' ')
    left++;

if (s[left] == '+')
    left++;
else if (s[left] == '-') {
sign = -1;
left++;}

int right = left;
while(isdigit(s[right]))
    right++;

if (left == right)
    cout << 0 << endl;
for (int i = right - 1; i >= left; i--) {
}
*/
