#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	// 0 <= n < (1 << 32)
	// Find distince positive integers a, b, c, and d such that 
	// they are <= 10^18 and ((a & b) | c) ^ d = N

	// If there are multiple answers, print any of them. If no answer
	// exists, print -1

	// N 0 0 0 0 0 0 0
	// a 1 1 0 1
	// b 1 0 0 0
	// c 0 1 0 0
	// d 1 1 0 0

	// 63 ... 56 55 54 53 52 51 .... 1 0

    // atleast one 1, and one 0 is now possible
    int a = 0, b = 0, c = 0, d = 0;
    for (int bit = 0; bit <= 51; bit++)
    	if (n & (1LL << bit))
    		a &= ~(1LL << bit), b &= ~(1LL << bit), c |= (1LL << bit), d &= ~(1LL << bit);
    	else 
    		a |= (1LL << bit), b |= (1LL << bit), c |= (1LL << bit), d |= (1LL << bit);

    auto set4 = [&](int &x, int b3, int b2, int b1, int b0) {
        // b3 = bit55, b0 = bit52
    	if (b0) x |= (1LL << 52); else x &= ~(1LL << 52);
    	if (b1) x |= (1LL << 53); else x &= ~(1LL << 53);
    	if (b2) x |= (1LL << 54); else x &= ~(1LL << 54);
    	if (b3) x |= (1LL << 55); else x &= ~(1LL << 55);
	};

	// a = 1101  (55→52)
	set4(a, 1, 1, 0, 1);
	
	// b = 1000
	set4(b, 1, 0, 0, 0);
	
	// c = 0100
	set4(c, 0, 1, 0, 0);
	
	// d = 1100
	set4(d, 1, 1, 0, 0);
    cout << a << " " << b << " " << c << " " << d << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}