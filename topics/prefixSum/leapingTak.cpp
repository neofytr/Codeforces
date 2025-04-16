#include <bits/stdc++.h>
using namespace std;

#define MOD 998244353

int main()
{
	long long n, k;
	cin >> n >> k;

	vector<pair<long long, long long>> segments(k);
	for (auto &segment : segments)
	{
		cin >> segment.first >> segment.second;
	}

	vector<long long> arr(n); // arr[i] = number of ways to reach index i
	vector<long long> prefix(n + 1); // prefix[i] = sum(arr[0..i-1])
	arr[0] = 1;
	prefix[1] = 1;

	for (long long index = 1; index < n; index++)
	{
		long long add = 0;
		for (auto segment : segments)
		{
			long long left = max(0LL, index - segment.second);
			long long right = index - segment.first;
			if (right < 0)
				continue;

			add = (add + prefix[right + 1] - prefix[left] + MOD) % MOD;
		}

		arr[index] = add;
		prefix[index + 1] = (prefix[index] + arr[index]) % MOD;
	}

	cout << arr[n - 1] << endl;
}
