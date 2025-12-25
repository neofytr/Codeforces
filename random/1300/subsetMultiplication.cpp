#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

long long gcd(long long a, long long b) {
    return std::gcd(a, b);
}

long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}

void solve() {
    int n;
    cin >> n;
    
    vector<long long> b(n);
    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    long long ans = 1;
    
    for(int i = 0; i < n - 1; i++) {
        long long necessary_factor = b[i] / gcd(b[i], b[i+1]);
        ans = lcm(ans, necessary_factor);
    }
    
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}