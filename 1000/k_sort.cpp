#include <bits/stdc++.h>
using namespace std;

#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define rep(i, a, b) for (int i = (a); i < (b); ++i)

struct subarr_t
{
    vector<pii> data;
    void compute_diffs(const vector<int> &arr, int base, const vector<int> &indexes)
    {
        for (int idx : indexes)
            data.pb({idx, base - arr[idx]});
    }
};

void print_subarr(const subarr_t &sub)
{
    for (auto &[idx, diff] : sub.data)
        cout << "(" << idx << ", " << diff << ") ";
    cout << endl;
}

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    vector<subarr_t> arr_of_subarr;
    int index = 0;

    while (index < n)
    {
        if (index >= 1 && arr[index - 1] > arr[index])
        {
            subarr_t sub;
            int base = arr[index - 1];
            vector<int> indexes;
            while (index < n && arr[index] < base)
            {
                indexes.pb(index);
                index++;
            }
            sub.compute_diffs(arr, base, indexes);
            arr_of_subarr.pb(sub);
            continue;
        }
        index++;
    }

    sort(all(arr_of_subarr), [](const subarr_t &a, const subarr_t &b)
         { return a.data < b.data; });
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
