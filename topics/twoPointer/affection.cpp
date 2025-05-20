#include <bits/stdc++.h>
using namespace std;

bool canAchieve(int target, int m, int c, vector<char> &garland)
{
    int left = 0;
    int right = 0;
    int n = garland.size();
    int repaint_left = m;

    while (left < n)
    {
        while (right < n)
        {
            if (garland[right] != c && repaint_left)
            {
                repaint_left--;
            }
            else if (garland[right] != c && !repaint_left)
            {
                break;
            }

            right++;

            if (right - left >= target)
            {
                return true;
            }
        }

        if (garland[left++] != c)
        {
            repaint_left++;
        }
    }

    return false;
}

int main()
{
    int n;
    cin >> n;

    vector<char> garland(n);
    for (char &color : garland)
    {
        cin >> color;
    }

    int q;
    cin >> q;

    int m;
    char c;

    while (q--)
    {
        cin >> m >> c;

        // if we can repaint to achieve a koyomity of atleast x, we can repaint to achieve a koyomity of x - 1; x > 1

        // a koyomity of atleast this much is possible since we can choose to repaint none (we can repaint atmost m)
        int left = 0;
        int right = garland.size() + 1; // a koyomity of this much is impossible

        while (right != left + 1)
        {
            int mid = left + (right - left) / 2;
            if (canAchieve(mid, m, c, garland))
            {
                left = mid;
            }
            else
            {
                right = mid;
            }
        }

        cout << left << endl;
    }

    return EXIT_SUCCESS;
}