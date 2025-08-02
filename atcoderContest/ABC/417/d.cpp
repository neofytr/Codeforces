#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int N;
vector<int> P, A, B;

ll simulate(ll mood) {
    for (int i = 0; i < N; ++i) {
        if (P[i] >= mood) {
            mood += A[i];
        } else {
            mood = max(0LL, mood - B[i]);
        }
    }
    return mood;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    P.resize(N);
    A.resize(N);
    B.resize(N);

    for (int i = 0; i < N; ++i) {
        cin >> P[i] >> A[i] >> B[i];
    }

    const int MAX_PRE = 2000;
    vector<ll> precomputed(MAX_PRE + 1);
    for (int x = 0; x <= MAX_PRE; ++x) {
        precomputed[x] = simulate(x);
    }

    int Q;
    cin >> Q;
    while (Q--) {
        ll x;
        cin >> x;

        if (x <= MAX_PRE) {
            cout << precomputed[x] << '\n';
        } else {
            cout << simulate(x) << '\n';
        }
    }

    return 0;
}
