#include <bits/stdc++.h>
using namespace std;

#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr)

int maxLengthWithReplacement(const vector<char> &garland, int m, char target)
{
    int n = garland.size();
    int maxLen = 0;
    int change_left = m;
    int left = 0;
    int right = 0;

    while (left < n)
    {
        while (right < n)
        {
            if (garland[right] != target && change_left)
            {
                change_left--;
            }
            else if (garland[right] != target && !change_left)
            {
                break;
            }

            right++;
        }

        maxLen = max(maxLen, right - left);

        if (garland[left] != target)
        {
            change_left++;
        }

        left++;
    }

    return maxLen;
}

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    vector<char> garland(n);
    for (char &color : garland)
        cin >> color;

    int q;
    cin >> q;
    while (q--)
    {
        int m;
        char ch;
        cin >> m >> ch;
        cout << maxLengthWithReplacement(garland, m, ch) << "\n";
    }
    return 0;
}
