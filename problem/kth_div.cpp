#include <bits/stdc++.h>
using namespace std;

#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);

using ull = unsigned long long;
using ll = long long;
using ld = long double;
using vi = vector<int>;
using vull = vector<ull>;
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define rev(i, a, b) for (int i = (a); i >= (b); --i)
#define sz(x) (int)(x).size()
#define yes cout << "YES\n"
#define no cout << "NO\n"

#ifdef LOCAL
#define debug(x) cerr << #x << " = " << (x) << endl;
#else
#define debug(x)
#endif

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

ll power(ll a, ll b, ll m = MOD)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

vull get_divisors(ull n)
{
    vull divs;
    for (ull index = 0; index * index <= n; index++)
    {
        if (n % index)
        {
            divs.push_back(index);
            if (n / index != n)
            {
                divs.push_back(index);
            }
        }
    }

    return divs;
}

void solve()
{
    size_t n, k;
    cin >> n >> k;

    size_t div_no = 0;

    for (size_t index = 1; index < n; index++)
    {
        if (!(n % index))
        {
            div_no++;
            if (div_no == k)
            {
                cout << index << endl;
                return;
            }
        }
    }

    cout << -1 << endl;
}

int main()
{
    FAST_IO;
    solve();
    return 0;
}
