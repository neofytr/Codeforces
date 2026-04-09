#include <bits/stdc++.h>
using namespace std;

#define int long long 

// x -> number of single tickets
// y -> number of special tickets

// x >= 0, y >= 0
// y * m + x = n
// cost = x * a + y * b

// x = n - y * m >= 0
// 0 <= y <= n / m
// cost = a * (n - y * m) + y  * b 
// = y * (b - a * m) + a * n
// 0 <= y <= n / m


#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;

    int cost_all_single = n * a;
    int cost_all_special = ((n + m - 1) / m) * b;
    int cost_mixed = (n / m) * b + (n % m) * a;

    cout << min({cost_all_single, cost_all_special, cost_mixed}) << endl;
    return 0;
}
