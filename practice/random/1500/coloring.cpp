#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n,m,k;
	cin>>n>>m>>k;

	vector<int>a(m);
	for(int &x:a) cin>>x;

	int q = n/k;
	int r = n%k;

	int big=0;

	for(int x:a){
		if(x>q+1){
			cout<<"NO\n";
			return;
		}
		if(x==q+1) big++;
	}

	if(big>r) cout<<"NO\n";
	else cout<<"YES\n";
}

int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	cin>>t;
	while(t--) solve();
}