#include <bits/stdc++.h>
using namespace std;

#define int long long 

int findClosest(const vector<int>& arr, int x) {
    int left = 1;
    int right = (int)arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == x)
            return arr[mid];
        else if (arr[mid] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }

    if (left >= (int)arr.size()) return arr[right];
    if (right < 1) return arr[left];

    if (abs(arr[left] - x) < abs(arr[right] - x))
        return arr[left];
    else
        return arr[right];
}

void solve() {
	int n, k;
	cin >> n >> k;

	int mini = LLONG_MAX;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r], mini = min(arr[r], mini);
	
	if (k >= 3) {
		cout << 0 << endl;
		return;
	} 

	if (k == 1) {
		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++)
				mini = min(mini, abs(arr[i] - arr[j]));

		cout << mini << endl;
		return;
	}

	if (k == 2) {
		sort(arr.begin(), arr.end());
		vector<int> d1, d2;
		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++)
				d1.push_back(abs(arr[i] - arr[j]));

		for (int x : d1)
			d2.push_back(abs(x - findClosest(arr, x)));

		for (int x : d1)
			mini = min(x, mini);
		for (int x : d2)
			mini = min(x, mini);

		cout << mini << endl;
	}
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}