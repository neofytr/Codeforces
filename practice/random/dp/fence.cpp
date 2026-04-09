#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
  	int n, k;
  	cin >> n >> k;
	
  	vector<int> h(n + 1);
  	for (int r = 1; r <= n; r++)
  	  cin >> h[r];

  	int mini = 0, minIdx = 1;
  	for (int r = 1; r <= k; r++)
  		mini += h[r];

  	int sum = mini;
  	for (int r = k + 1; r <= n; r++) {
  		sum += h[r], sum -= h[r - k];
  		if (sum <= mini) mini = sum, minIdx = r - k + 1;
  	}

    cout << minIdx << endl;
    return 0;
}