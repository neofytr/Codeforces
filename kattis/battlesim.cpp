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
}

bool is_combo(int index, std::string &moves)
{
    if ((moves[index] == 'R' && moves[index + 1] == 'B' && moves[index + 2] == 'L') ||
        (moves[index] == 'R' && moves[index + 1] == 'L' && moves[index + 2] == 'B') ||
        (moves[index] == 'B' && moves[index + 1] == 'R' && moves[index + 2] == 'L') ||
        (moves[index] == 'B' && moves[index + 1] == 'L' && moves[index + 2] == 'R') ||
        (moves[index] == 'L' && moves[index + 1] == 'R' && moves[index + 2] == 'B') ||
        (moves[index] == 'L' && moves[index + 1] == 'B' && moves[index + 2] == 'R'))
    {
        return true;
    }
    return false;
}

int main()
{
    string moves;
    cin >> moves;

    int len = moves.length();
    int index = 0;

    while (index < len)
    {
        if (index < len - 3 && is_combo(index, moves))
        {
            printf("C");
            index += 3;
            continue;
        }

        if (moves[index] == 'R')
        {
            printf("S");
        }

        if (moves[index] == 'B')
        {
            printf("K");
        }

        if (moves[index] == 'L')
        {
            printf("H");
        }

        index++;
    }
    return 0;
}
