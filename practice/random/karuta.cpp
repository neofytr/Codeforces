#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(26)

struct Node {
	Node *arr[MAX];
	bool end; int cnt;

	Node() {
		for (int i = 0; i < MAX; i++) arr[i] = nullptr;
		end = false, cnt = 0;
	}
};

Node *root;
void insert(string &s) {
	Node *curr = root;
	for (int i = 0; i < s.length(); i++) {
		int c = s[i] - 'a';
		if (!curr->arr[c]) curr->arr[c] = new Node();
		curr = curr->arr[c];
	}
	curr->end = true; curr->cnt++;
}

int32_t main() {
	int n; cin >> n;
	vector<string> a(n);
	for (string &s : a) cin >> s;

	root = new Node();
	for (string &s : a) insert(s);
	for (int i = 0; i < n; i++) {
		Node *curr = root;
		int maxi = -1;
		for (int j = 0; j < a[i].length(); j++) {
			int c = a[i][j] - 'a';
			curr = curr->arr[c];
			if (curr->end) 
				if (j + 1 < a[i].length() || curr->cnt > 1)
					maxi = max(maxi, j + 1);
		}
		if (curr->cnt > 1) maxi = max(maxi, (int)a[i].length());
		cout << maxi << endl;
	}
	return 0;
}