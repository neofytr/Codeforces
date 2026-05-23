#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(26)

struct Node {
	Node *arr[MAX];
	Node() {
		for (int i = 0; i < MAX; i++) arr[i] = nullptr;
	}
};

int res = 0; Node *root;
int32_t main() {
	root = new Node();
	string s; cin >> s;
	int n = s.length();
	vector<int> str(n + 1);
	for (int i = 1; i <= n; i++) str[i] = s[i - 1] - 'a';

	cin >> s;
	vector<int> f(26);
	for (int i = 0; i < 26; i++)
		f[i] = s[i] - '0';

	int k; cin >> k;
	int r = 1; int cnt = 0;
	for (int l = 1; l <= n; l++) {
		while (r <= n && cnt + (!f[str[r]]) <= k) {
			if (!f[str[r]]) cnt++;
			r++;
		}

		if (l <= r - 1) {
			Node *curr = root;
			for (int i = l; i <= r - 1; i++) {
				int c = str[i];
				if (!curr->arr[c])
					res++, curr->arr[c] = new Node();
				curr = curr->arr[c];
			}
		}
		if (!f[str[l]]) cnt--;
	}

	cout << res << endl;
	return 0;
}