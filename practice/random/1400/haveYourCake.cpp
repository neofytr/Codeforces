#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; 
	cin >> n;

	vector<int> A(n + 1), B(n + 1), C(n + 1);
	for (int i = 1; i <= n; i++) cin >> A[i];
	for (int i = 1; i <= n; i++) cin >> B[i];
	for (int i = 1; i <= n; i++) cin >> C[i];

	vector<int> pa(n + 1), pb(n + 1), pc(n + 1);
	for (int i = 1; i <= n; i++) {
		pa[i] = pa[i - 1] + A[i];
		pb[i] = pb[i - 1] + B[i];
		pc[i] = pc[i - 1] + C[i];
	}

	int need = (pa[n] + 2) / 3;

	auto try_mid = [&](vector<int>& X,
	                   vector<int>& pX,
	                   vector<int>& pY,
	                   vector<int>& pZ,
	                   int idX, int idY, int idZ) {

		int l = 1, sum = 0;
		for (int r = 1; r <= n; r++) {
			sum += X[r];
			while (l <= r && sum - X[l] >= need) {
				sum -= X[l++];
			}
			if (l <= r && sum >= need) {
				if (pY[l - 1] >= need && (pZ[n] - pZ[r]) >= need) {
					pair<int,int> seg[3];
					seg[idX] = {l, r};
					seg[idY] = {1, l - 1};
					seg[idZ] = {r + 1, n};

					for (int i = 0; i < 3; i++)
						cout << seg[i].first << " " << seg[i].second << " ";
					cout << "\n";
					return true;
				}
				if (pZ[l - 1] >= need && (pY[n] - pY[r]) >= need) {
					pair<int,int> seg[3];
					seg[idX] = {l, r};
					seg[idZ] = {1, l - 1};
					seg[idY] = {r + 1, n};

					for (int i = 0; i < 3; i++)
						cout << seg[i].first << " " << seg[i].second << " ";
					cout << "\n";
					return true;
				}
			}
		}
		return false;
	};

	if (try_mid(A, pa, pb, pc, 0, 1, 2)) return; 
	if (try_mid(B, pb, pa, pc, 1, 0, 2)) return; 
	if (try_mid(C, pc, pa, pb, 2, 0, 1)) return; 

	cout << -1 << "\n";
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t; 
	cin >> t;
	while (t--) solve();
	return 0;
}
