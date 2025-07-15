#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<long long> black(n);
    vector<long long> white(m);

    for (long long &val : black)
    {
        cin >> val;
    }

    for (long long &val : white)
    {
        cin >> val;
    }

    // sort in non-increasing order
    sort(black.rbegin(), black.rend());
    sort(white.rbegin(), white.rend());

    vector<long long> prefixBlack(n + 1, 0);
    vector<long long> prefixWhite(m + 1, 0);

    for (int index = 1; index <= n; index++)
    {
        prefixBlack[index] = prefixBlack[index - 1] + black[index - 1];
    }

    for (int index = 1; index <= m; index++)
    {
        prefixWhite[index] = prefixWhite[index - 1] + white[index - 1];
    }

    long long maximum = 0;

    for (int whiteCount = 0; whiteCount <= m; whiteCount++)
    {
        if (whiteCount <= n)
        {
            int blackCount = whiteCount;
            while (blackCount < n && black[blackCount] > 0)
            {
                blackCount++;
            }

            int maxPossibleWhite = min(blackCount, m);
            long long currentSum = 0;

            for (int w = 0; w < maxPossibleWhite; w++)
            {
                if (white[w] > 0)
                {
                    currentSum += white[w];
                }
                else
                {
                    break;
                }
            }

            currentSum += prefixBlack[blackCount];

            maximum = max(maximum, currentSum);
        }
    }

    cout << maximum << endl;
    return 0;
}