#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<long long> min_round(n);
    for (long long &val : min_round)
    {
        cin >> val;
    }

    // during each round, exactly one of the n players is the supervisor and the rest play
    // rth player wants to play min_round[r] number of rounds at least; 0 <= r < n
    // we want the minimum number of rounds (say x) such that everyone gets to play at least as much as they want

    // first, note that in x rounds, a player can play at most x times (if never a supervisor)
    // so x must be >= max(min_round[r]) for all r
    // otherwise, someone wants to play more than x times, which is impossible

    // second, in x rounds, exactly one player sits out in each round (supervisor)
    // so total number of "missed rounds" across all players is at most x

    // if player r wants to play min_round[r], then they must sit out at most (x - min_round[r]) rounds
    // so for all players, the total number of rounds they sit out is at most:
    // sum(x - min_round[r]) for all r = n*x - sum(min_round)

    // but we know total number of sit-outs is at most x (since one person sits out per round)
    // so: n*x - sum(min_round) <= x
    // rearranging: (n - 1)*x <= sum(min_round)
    // so: x >= ceil(sum(min_round) / (n - 1))

    // final result must satisfy both conditions:
    // x >= max(min_round[r])      (no one plays more than x)
    // x >= ceil(sum / (n - 1))    (total sit-outs don't exceed x)

    // so the answer is max(max_a, (sum + n - 2) / (n - 1))

    long long sum = 0, max_a = 0;
    for (long long val : min_round)
    {
        sum += val;
        max_a = max(max_a, val);
    }

    long long answer = max(max_a, (sum + n - 2) / (n - 1));
    cout << answer << endl;

    return EXIT_SUCCESS;
}
