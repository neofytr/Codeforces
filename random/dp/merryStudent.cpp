#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX_N 500
#define MAX_K 100

int k[MAX_N + 1];
int p[MAX_N + 1][MAX_K + 1];
int w[MAX_N + 1][MAX_K + 1];

int ord[MAX_N + 1][MAX_K + 1];
int cls[MAX_N + 1];

int ordsum[MAX_N + 1];
int wsum[MAX_N + 1];
int psum[MAX_N + 1];

int curr;

auto cmpwithin = [](int a, int b) {
	int t1 = (int)w[curr][a] * p[curr][a]
	            + (int)w[curr][b] * (p[curr][a] + p[curr][b]);
	int t2 = (int)w[curr][b] * p[curr][b]
	            + (int)w[curr][a] * (p[curr][a] + p[curr][b]);
	return t1 < t2;
};

auto cmpclass = [](int a, int b) {
	int t1 = ordsum[a] + (int)psum[a] * wsum[b] + ordsum[b];
	int t2 = ordsum[b] + (int)psum[b] * wsum[a] + ordsum[a];
	return t1 < t2;
};

int32_t main() {
	freopen("student.in", "r", stdin);
	freopen("student.out", "w", stdout);

	int n;
	cin >> n;

	for (int i = 1; i <= n; i++)
		cin >> k[i];

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= k[i]; j++)
			cin >> p[i][j];

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= k[i]; j++)
			cin >> w[i][j];

	for (int i = 1; i <= n; i++) {
		wsum[i] = psum[i] = 0;
		for (int j = 1; j <= k[i]; j++) {
			wsum[i] += w[i][j];
			psum[i] += p[i][j];
			ord[i][j] = j;
		}
	}

	for (int i = 1; i <= n; i++) {
		curr = i;
		sort(ord[i] + 1, ord[i] + k[i] + 1, cmpwithin);

		int t = 0;
		ordsum[i] = 0;
		for (int j = 1; j <= k[i]; j++) {
			int lab = ord[i][j];
			t += p[i][lab];
			ordsum[i] += t * w[i][lab];
		}
	}

	for (int i = 1; i <= n; i++)
		cls[i] = i;

	sort(cls + 1, cls + n + 1, cmpclass);

	int gid = 1;
	static int lab_id[MAX_N + 1][MAX_K + 1];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= k[i]; j++)
			lab_id[i][j] = gid++;

	long long total_cost = 0;
	long long cur_time = 0;

	for (int i = 1; i <= n; i++) {
		int c = cls[i];
		for (int j = 1; j <= k[c]; j++) {
			int lab = ord[c][j];
			cur_time += p[c][lab];
			total_cost += cur_time * w[c][lab];
		}
	}

	cout << total_cost << "\n";
	for (int i = 1; i <= n; i++) {
		int c = cls[i];
		for (int j = 1; j <= k[c]; j++) {
			int lab = ord[c][j];
			cout << lab_id[c][lab] << " ";
			cur_time += p[c][lab];
			total_cost += cur_time * w[c][lab];
		}
	}
	cout << "\n";

	return 0;
}
