#include <bits/stdc++.h>
using namespace std;

#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);

using ll = long long;
using ld = long double;
using vi = vector<int>;
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

void solve()
{
    int n, m, k;

    cin >> n >> m >> k;
    vector<int> a(n);
    vector<int> b(m);

    vector<int> final(k);

    for (int &val : a)
    {
        cin >> val;
    }

    for (int &val : b)
    {
        cin >> val;
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int a_index = 0, b_index = 0;
    int curr = 0;

    while (curr < k)
    {
        if (a[a_index] == curr + 1 && b[b_index] != curr + 1)
        {
            final[curr] = a[a_index];
            a_index++;
        }

        if (b[b_index] == curr + 1 && a[a_index] != curr + 1)
        {
            final[curr] = b[b_index];
            b_index++;
        }

        if (a[a_index] == curr + 1 && b[b_index] == curr + 1)
        {
            final[curr] = b[b_index];
            a_index++;
            b_index++;
        }

        if (a[a_index] != curr + 1 && b[b_index] != curr + 1)
        {
            no;
            return;
        }
    }

    if (a_index != b_index)
    {
        no;
        return;
    }

    yes;
}

int main()
{
    FAST_IO;
    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }
    return 0;
}
