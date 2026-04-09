#include <iostream>
#include <vector>
using namespace std;

int round_winner(int x, int y)
{
    if (x > y)
        return 1; // Suneet wins the round
    if (x < y)
        return -1; // Slavic wins the round
    return 0;      // Tie
}

int count_wins(int a1, int a2, int b1, int b2)
{
    vector<pair<int, int>> suneet_cards = {{a1, a2}, {a2, a1}};
    vector<pair<int, int>> slavic_cards = {{b1, b2}, {b2, b1}};
    int win_count = 0;

    for (auto suneet : suneet_cards)
    {
        for (auto slavic : slavic_cards)
        {
            int suneet_score = 0, slavic_score = 0;

            int result = round_winner(suneet.first, slavic.first);
            if (result == 1)
                suneet_score++;
            else if (result == -1)
                slavic_score++;

            result = round_winner(suneet.second, slavic.second);
            if (result == 1)
                suneet_score++;
            else if (result == -1)
                slavic_score++;

            if (suneet_score > slavic_score)
            {
                win_count++;
            }
        }
    }
    return win_count;
}

void solve()
{
    int a1, a2, b1, b2;
    cin >> a1 >> a2 >> b1 >> b2;
    cout << count_wins(a1, a2, b1, b2) << "\n";
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}