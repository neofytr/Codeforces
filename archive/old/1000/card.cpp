#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    priority_queue<int> alice;
    set<int> bob;

    for (int i = 0; i < n; ++i)
    {
        if (s[i] == 'A')
        {
            alice.push(i + 1);
        }
        else
        {
            bob.insert(i + 1);
        }
    }

    while (true)
    {
        if (alice.empty())
        {
            cout << "Bob\n";
            break;
        }
        if (bob.empty())
        {
            cout << "Alice\n";
            break;
        }

        int alice_turn = alice.top();

        if (alice_turn == n)
        {
            // Alice plays card n, Bob's chance to beat with 1
            auto it = bob.find(1);
            if (it != bob.end())
            {
                // Bob has 1, he wins this round
                alice.pop();
                bob.insert(n);
            }
            else
            {
                // Bob doesn't have 1, Alice wins this round
                auto beat_it = bob.begin(); // Bob plays his smallest card
                alice.push(*beat_it);
                bob.erase(beat_it);
            }
        }
        else
        {
            auto it = bob.upper_bound(alice_turn);
            if (it != bob.end())
            {
                // Bob can beat Alice's card
                alice.pop();
                bob.insert(alice_turn);
            }
            else
            {
                // Bob can't beat Alice's card, Alice wins this round
                auto beat_it = bob.begin(); // Bob plays his smallest card
                alice.push(*beat_it);
                bob.erase(beat_it);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}