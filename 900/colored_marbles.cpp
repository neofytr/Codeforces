#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>

using namespace std;

int solve(vector<int> &marbles)
{
    int n = marbles.size();

    unordered_map<int, int> freq;
    for (int x : marbles)
    {
        freq[x]++;
    }

    map<int, vector<int>> freq_to_colors;
    for (auto &[color, count] : freq)
    {
        freq_to_colors[count].push_back(color);
    }

    int score = 0;
    bool aliceTurn = true; // true for Alice's turn, false for Bob's
    int remaining_moves = n;

    for (auto &[frequency, colors] : freq_to_colors)
    {
        for (int color : colors)
        {
            if (frequency == 1)
            {
                if (aliceTurn)
                {
                    score += 2;
                }
                aliceTurn = !aliceTurn;
                remaining_moves--;
            }
            else
            {
                int marbles_alice_can_get;
                if (aliceTurn)
                {
                    marbles_alice_can_get = (frequency + 1) / 2;
                }
                else
                {
                    marbles_alice_can_get = frequency / 2;
                }

                if (marbles_alice_can_get > 0)
                {
                    score += 1;
                    if (marbles_alice_can_get == frequency)
                    {
                        score += 1;
                    }
                }

                aliceTurn = ((remaining_moves - frequency) % 2 == 0) ? aliceTurn : !aliceTurn;
                remaining_moves -= frequency;
            }
        }
    }

    return score;
}

int main()
{
    int t;
    cin >> t;

    for (int test_case = 0; test_case < t; test_case++)
    {
        int n;
        cin >> n;
        vector<int> marbles(n);
        for (int &x : marbles)
        {
            cin >> x;
        }

        cout << solve(marbles) << endl;
    }

    return 0;
}