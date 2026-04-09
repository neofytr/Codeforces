#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX (int)(5 * 1e5)
#define OFFSET MAX

int str[MAX + 1];
int cnt[MAX * 2 + 1];
int32_t main() {
	int n;
	cin >> n;

	string s;
	cin >> s;

	for (int r = 1; r <= n; r++) str[r] = s[r - 1] - 'A';

	int sum = 0, d = 0, res = 0;
	cnt[d + OFFSET] = 1;

	for (int r = 1; r <= n; r++) {
		if (!str[r])
			sum += cnt[d + OFFSET], d++, cnt[d + OFFSET]++, res += sum;
		if (str[r] == 1)
			sum -= cnt[d - 1 + OFFSET], d--, cnt[d + OFFSET]++, res += sum;
		if (str[r] == 2)
			cnt[d + OFFSET]++, res += sum;
	}

	cout << res << endl;
	return 0;
}