#include <bits/stdc++.h>
using namespace std;

#define int long long
#define BIT (int)(2)

struct Node {
	Node *arr[BIT];
	Node() {
		for (int i = 0; i < BIT; i++) arr[i] = nullptr;
	}
};

Node *rooteven, *rootodd;
void insert_even(int num) {
	Node *curr = rooteven;
	for (int bit = 29; bit >= 0; bit--) {
		int c = (num >> bit) & 1;
		if (!curr->arr[c]) curr->arr[c] = new Node();
		curr = curr->arr[c];
	}
}
void insert_odd(int num) {
	Node *curr = rootodd;
	for (int bit = 29; bit >= 0; bit--) {
		int c = (num >> bit) & 1;
		if (!curr->arr[c]) curr->arr[c] = new Node();
		curr = curr->arr[c];
	}
}


int32_t main() {
	int n, m; cin >> n >> m;
	vector<int> v(n + 1), u(m + 1);
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (int i = 1; i <= m; i++) cin >> u[i];

	vector<int> pv(n + 1, 0), pu(m + 1, 0);
	for (int i = 1; i <= n; i++) pv[i] = pv[i - 1] ^ v[i];
	for (int i = 1; i <= m; i++) pu[i] = pu[i - 1] ^ u[i];

	rootodd = new Node(), rooteven = new Node();
	for (int c1 = 1; c1 <= m; c1++)
		for (int c2 = c1; c2 <= m; c2++)
			if ((c2 - c1 + 1) & 1) insert_odd(pu[c2] ^ pu[c1 - 1]);
			else insert_even(pu[c2] ^ pu[c1 - 1]);

	int maxi = 0;
	for (int r1 = 1; r1 <= n; r1++)
		for (int r2 = r1; r2 <= n; r2++) 
			if (!((r2 - r1 + 1) & 1)) {
				if (m >= 2)
					maxi = max(maxi, 0ll); // if c2 - c1 + 1 is even
				maxi = max(maxi, pv[r2] ^ pv[r1 - 1]);
			} else {
				// assume c2 - c1 + 1 is even
				// possible iff m >= 2
				int p = 0;
				Node *currnode = rooteven; int curr = 0;
				if (m >= 2) {
					for (int bit = 29; bit >= 0; bit--) {
						int want = !((p >> bit) & 1);
						if (!currnode->arr[want]) curr |= ((!want) << bit), currnode = currnode->arr[!want];
						else curr |= (want << bit), currnode = currnode->arr[want];
					}
					maxi = max(maxi, p ^ curr);
				}

				// assume c2 - c1 + 1 is odd
				p = pv[r2] ^ pv[r1 - 1];
				currnode = rootodd; curr = 0;
				for (int bit = 29; bit >= 0; bit--) {
					int want = !((p >> bit) & 1);
					if (!currnode->arr[want]) curr |= ((!want) << bit), currnode = currnode->arr[!want];
					else curr |= (want << bit), currnode = currnode->arr[want];
				}
				maxi = max(maxi, p ^ curr);
				
			}

	cout << maxi << endl;
	return 0;
}