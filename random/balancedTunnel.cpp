#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (100000)

int32_t main() {
    int n;
    cin >> n;

    int val;
    vector<int> enter(n + 1), exit(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> val, enter[val] = r;

    for (int r = 1; r <= n; r++)
        cin >> exit[r];

    int cnt = 0;
    int mini = enter[exit[n]];
    for (int time = n - 1; time >= 1; time--) {
        int car = exit[time];
        int arrival = enter[car];
        if (arrival >= mini)
            cnt++;
        mini = min(arrival, mini);
    }

    cout << cnt << endl;
    return 0;
}