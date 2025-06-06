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

void get_divisors(ull n, vull &divs)
{
    for (ull index = 1; index * index <= n; index++)
    {
        if (n % index)
        {
            divs.push_back(index);
            if (n / index != index)
            {
                divs.push_back(index);
            }
        }
    }

    sort(all(divs));
}

void solve()
{
    string str;
    cin >> str;

    string original = str;

    vector<int> indexes;

    int zero = 0, one = 0;
    for (char ch : str)
    {
        if (ch == '0')
        {
            zero++;
        }
        else
        {
            one++;
        }
    }

    if (zero == one)
    {
        cout << 0 << endl;
        return;
    }

    int cost = 0;

    if (zero > one)
    {
        for (int index = str.length() - 1; index >= 0; index--)
        {
            if (str[index] == '1')
            {
                indexes.push_back(index);
            }
        }

        for (int index = 0; index < str.length(); index++)
        {
            if (str[index] == '0' && original[index] == '0')
            {
                if (!indexes.size())
                {
                    cost++;
                    str.erase(index, 1);
                    index--;
                    continue;
                }
                int swap = indexes.back();
                indexes.pop_back();

                str[index] = '1';
                str[swap] = '0';
            }
        }
    }
    else
    {
        for (int index = str.length() - 1; index >= 0; index--)
        {
            if (str[index] == '0')
            {
                indexes.push_back(index);
            }
        }

        for (int index = 0; index < str.length(); index++)
        {
            if (str[index] == '1' && original[index] == '1')
            {
                if (!indexes.size())
                {
                    cost++;
                    str.erase(index, 1);
                    index--;
                    continue;
                }
                int swap = indexes.back();
                indexes.pop_back();

                str[index] = '0';
                str[swap] = '1';
            }
        }
    }

    cout << cost << endl;
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
