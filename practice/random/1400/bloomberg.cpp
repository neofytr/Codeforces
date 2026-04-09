#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, target;
	cin >> n >> target;

	vector<int> arr(n + 2);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	arr[0] = LLONG_MIN;
	arr[n + 1] = LLONG_MAX;
	int left = 0;
	int right = n + 1;

	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if (arr[mid] < target) left = mid;
		else right = mid;
	}

	cout << (arr[right] == target ? right - 1 : -1) << " ";
	left = 0, right = n + 1;
	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if (arr[mid] > target) right = mid;
		else left = mid;
	}

	cout << (arr[left] == target ? left - 1 : -1) << endl;
	return 0;
}