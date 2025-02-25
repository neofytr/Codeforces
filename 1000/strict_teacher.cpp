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

bool is_caught(int t_one, int t_two, int david)
{
    return abs(t_one - david) == 1 || abs(t_two - david) == 1;
}

void solve()
{
    int n, m, q;

    cin >> n >> m >> q;

    int t_one_curr, t_two_curr, david_curr;

    cin >> t_one_curr >> t_two_curr;
    cin >> david_curr;

    int moves = 0;

    do
    {
        // ideal david move
        // increase his distance from the closest teacher, or don't move if you can't

        int dist_one = t_one_curr - david_curr;
        int dist_two = t_two_curr - david_curr;

        if (abs(dist_one) > abs(dist_two))
        {
            if (dist_one > 0 && david_curr)
            {
                david_curr--;
            }
            else if (dist_one < 0 && david_curr != n - 1)
            {
                david_curr++;
            }
        }
        else if (abs(dist_one) < abs(dist_two))
        {
            if (dist_two > 0 && david_curr)
            {
                david_curr--;
            }
            else if (dist_two < 0 && david_curr != n - 1)
            {
                david_curr++;
            }
        }

        if (dist_one > 0)
        {
            t_one_curr--;
        }
        else if (dist_one < 0)
        {
            t_one_curr++;
        }

        if (dist_two > 0)
        {
            t_two_curr--;
        }
        else if (dist_two < 0)
        {
            t_two_curr++;
        }

        moves++;
    } while (!is_caught(t_one_curr, t_two_curr, david_curr));

    printf("%d\n", moves);
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
