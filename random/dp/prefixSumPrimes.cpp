#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int arr[MAX + 1];
bitset<2 * MAX + 1> notPrime(false);
vector<int> primes;

int32_t main() {
	int n;
	cin >> n;

	int v;
	int cntOne = 0, cntTwo = 0;
	for (int r = 1; r <= n; r++) {
		cin >> v;
		if (v == 1) cntOne++;
		else cntTwo++;
	}

	notPrime[0] = notPrime[1] = true;
	for (int r = 2; r <= 2 * n; r++)
		if (!notPrime[r])
			for (int j = r * r; j <= 2 * n; j += r)
				notPrime[j] = true;

	for (int r = 2; r <= 2 * n; r++)
		if (!notPrime[r]) primes.push_back(r);

	if (!cntOne) {
		for (int r = 1; r <= n; r++)
			cout << 2 << " ";
		cout << endl;
		return 0;
	}

	int prev = 0;
	int r = 1;
	for (int p : primes) {
		int req = p - prev;
		int twos = min(cntTwo, req / 2);
		int ones = min(cntOne, req - 2 * twos);

		cntTwo -= twos, cntOne -= ones;
		for (int i = 1; i <= twos; i++)
			arr[r++] = 2;
		for (int i = 1; i <= ones; i++)
			arr[r++] = 1;

		prev = p;
	}

	for (int r = 1; r <= n; r++)
		cout << arr[r] << " ";
	cout << endl;
	return 0;
}