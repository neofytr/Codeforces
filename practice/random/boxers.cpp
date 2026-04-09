#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAX = 150000;

int f[MAX + 1];
bool done[MAX + 2];

int32_t main() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	sort(arr.rbegin(), arr.rend() - 1);

	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		int r = arr[i];
		if (!done[r + 1])
			done[r + 1] = true, cnt++;
		else if (!done[r])
			done[r] = true, cnt++;
		else if (r > 1 && !done[r - 1])
			done[r - 1] = true, cnt++;
	}

	cout << cnt << endl;
}

int32_t main2() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> diff;
    for (int r = 1; r <= n; r++) {
        int val;
        cin >> val;
        if (!f[val])
            diff.push_back(val);
        f[val]++;
    }

    unordered_map<int, int> edge; // keeps track of used positions outside segments
    sort(diff.begin(), diff.end());

    int res = 0;
    int sz = diff.size();
    int i = 0;

    while (i < sz) {
        int j = i;
        int s = 0;

        // find consecutive segment
        while (j < sz - 1 && diff[j + 1] == diff[j] + 1) {
            s += f[diff[j]];
            j++;
        }
        s += f[diff[j]];

        int range = diff[j] - diff[i] + 1;

        if (s == range) {
            res += range;
        } 
        else if (s == range + 1) {
            if (diff[i] == 1) {
                edge[diff[j] + 1] = true;
                res += range + 1;
            } else {
                if (!edge[diff[i] - 1]) {
                    edge[diff[i] - 1] = true;
                    res += range + 1;
                } else {
                    edge[diff[j] + 1] = true;
                    res += range + 1;
                }
            }
        } 
        else if (s >= range + 2) {
            if (diff[i] == 1) {
                edge[diff[j] + 1] = true;
                res += range + 1;
            } else {
                res += range + 2;
                edge[diff[j] + 1] = true;
                if (edge[diff[i] - 1])
                    res--;
            }
        }

        i = j + 1;
    }

    cout << res << "\n";
    return 0;
}
