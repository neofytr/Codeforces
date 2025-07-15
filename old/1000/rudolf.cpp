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
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
    {
        cin >> val;
    }

    // n >= 3 (given)

    int left = 0, right = n - 1;

    while (left <= right)
    {
        if (!arr[left])
        {
            left++;
        }
        else
        {
            if (arr[left + 1] >= 2 * arr[left] && arr[left + 2] >= arr[left])
            {
                arr[left + 1] -= 2 * arr[left];
                arr[left + 2] -= arr[left];
                arr[left] = 0;
                left++;
            }
            else
            {
                no;
                return;
            }
        }

        if (!arr[right])
        {
            right--;
        }
        else
        {
            if (arr[right - 1] >= 2 * arr[right] && arr[right - 2] >= arr[right])
            {
                arr[right - 1] -= 2 * arr[right];
                arr[right - 2] -= arr[right];
                arr[right] = 0;
                right--;
            }
            else
            {
                no;
                return;
            }
        }
    }

    yes;
    return;
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
