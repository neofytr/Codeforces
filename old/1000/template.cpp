#include <iostream>
#include <vector>
#include <unordered_map>

#define FAST_IO              \
    ios::sync_with_stdio(0); \
    cin.tie(0);

using namespace std;

void solve()
{
    int n, m;
    cin >> n;

    vector<int> int_arr(n);
    unordered_map<int, int> int_unique;
    int index = 0;

    for (int &val : int_arr)
    {
        cin >> val;
        if (int_unique.find(val) == int_unique.end()) // Fix: Check if not found
        {
            int_unique[val] = index++; // Fix: Correct insertion
        }
    }

    vector<int> customized_int(n);
    for (int i = 0; i < n; i++) // Fix: Iterate over int_arr, not customized_int
    {
        customized_int[i] = int_unique[int_arr[i]];
    }

    cin >> m;
    if (n != m)
    {
        cout << "NO\n";
        return;
    }

    vector<int> char_arr(n);
    unordered_map<int, int> char_unique;
    int char_index = 0;

    for (int &val : char_arr)
    {
        cin >> val;
        if (char_unique.find(val) == char_unique.end()) // Fix: Check if not found
        {
            char_unique[val] = char_index++; // Fix: Correct insertion
        }
    }

    vector<int> customized_char(n);
    for (int i = 0; i < n; i++) // Fix: Iterate over char_arr, not customized_char
    {
        customized_char[i] = char_unique[char_arr[i]];
    }

    if (customized_char == customized_int)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
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
