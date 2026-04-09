#include <bits/stdc++.h>
using namespace std;

#define int long long

void arraySort(vector<int> &arr, int left, int right) {
	if (left == right)
		return;

	int m = left + (right - left) / 2;
	arraySort(arr, left, m);
	arraySort(arr, m + 1, right);

	vector<int> tmp(right - left + 2);
	int i = left, j = m + 1, k = 1;
	while (i <= m && j <= right)
		if (arr[i] < arr[j])
			tmp[k++] = arr[i++];
		else 
			tmp[k++] = arr[j++];

	while(i <= m)
		tmp[k++] = arr[i++];
	while(j <= right)
		tmp[k++] = arr[j++];

	k = 1;
	for (int r = left; r <= right; r++)
		arr[r] = tmp[k++];
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r];

	arraySort(arr, 1, n);
	for (int r = 1; r <= n; r++)
		cout << arr[r] << " ";
	cout << endl;
	return 0;
}