#include <bits/stdc++.h>
using namespace std;

#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);

using ull = unsigned long long;
using ll = long long;
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

void get_divisors(ull n, vull &divs)
{
    for (ull index = 1; index * index <= n; index++)
    {
        if (n % index == 0)
        {
            divs.push_back(index);
            if (n / index != index)
            {
                divs.push_back(n / index);
            }
        }
    }
    sort(all(divs));
}

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> lists(m);
    for (int i = 0; i < m; i++)
    {
        cin >> lists[i];
    }

    vector<int> known(k);
    for (int i = 0; i < k; i++)
    {
        cin >> known[i];
    }

    sort(known.begin(), known.end()); // Ensure binary_search works

    if (k < n - 1)
    {
        for (int counter = 0; counter < m; counter++)
        {
            cout << 0;
        }
        cout << '\n';
        return;
    }

    if (k == n)
    {
        for (int counter = 0; counter < m; counter++)
        {
            cout << 1;
        }
        cout << '\n';
        return;
    }

    for (int counter = 0; counter < m; counter++)
    {
        int elt_to_exclude = lists[counter];
        bool good = true;

        for (int num : known)
        {
            if (num == elt_to_exclude)
                continue;

            if (!binary_search(known.begin(), known.end(), num))
            {
                good = false;
                cout << 0;
                break;
            }
        }

        if (good)
        {
            cout << 1;
        }
    }

    cout << '\n';
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
