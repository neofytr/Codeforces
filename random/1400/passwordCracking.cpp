#include <bits/stdc++.h>
using namespace std;

#define int long long

bool ask(deque<char> &dq) {
    string t;
    for (char c : dq)
        t.push_back(c);

    cout << "? " << t << endl;
    cout.flush();   

    bool res;
    cin >> res;
    return res;
}

void submit(deque<char> &dq) {
    string t;
    for (char c : dq)
        t.push_back(c);

    cout << "! " << t << endl;
    cout.flush();  
}

void solve() {
    int n; 
    cin >> n;

    deque<char> dq;

    while (dq.size() <= n - 1) {
        dq.push_back('0');
        if (!ask(dq)) {
            dq.pop_back();
            break;
        }
    }

    int i = 1;
    char A;
    while (true) {
    	if (i & 1) A = '1';
    	else A = '0';
        while (dq.size() <= n - 1) {
            dq.push_back(A);
            if (!ask(dq)) {
                dq.pop_back();
                break;
            }
        }

        while (dq.size() <= n - 1) {
            dq.push_front(A);
            if (!ask(dq)) {
                dq.pop_front();
                break;
            }
        }

        if (dq.size() >= n) break;
       	i++;
    }

    submit(dq);
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    cin >> t;
    while (t--) solve();

    return 0;
}
