// https://codeforces.com/problemset/problem/1730/B

#include <bits/stdc++.h>
using namespace std;

double point(double x, vector<double> &position, vector<double> &dress)
{
    // we can have max(|p - xi| + ti, 0 <= i <= n) <= x for any p in R
    double largest_left;
    double smallest_right;
    for (int index = 0; index < position.size(); index++)
    {
        if (x < dress[index])
        {
            return false;
        }

        double left = min(position[index] + dress[index] - x, position[index] - dress[index] + x);
        double right = max(position[index] + dress[index] - x, position[index] - dress[index] + x);

        if (!index)
        {
            largest_left = left;
            smallest_right = right;
        }
        else
        {
            largest_left = max(left, largest_left);
            smallest_right = min(right, smallest_right);
        }
    }

    return largest_left;
}

bool canMeet(double x, vector<double> &position, vector<double> &dress)
{
    // we can have max(|p - xi| + ti, 0 <= i <= n) <= x for any p in R
    double largest_left;
    double smallest_right;
    for (int index = 0; index < position.size(); index++)
    {
        if (x < dress[index])
        {
            return false;
        }

        double left = min(position[index] + dress[index] - x, position[index] - dress[index] + x);
        double right = max(position[index] + dress[index] - x, position[index] - dress[index] + x);

        if (!index)
        {
            largest_left = left;
            smallest_right = right;
        }
        else
        {
            largest_left = max(left, largest_left);
            smallest_right = min(right, smallest_right);

            if (largest_left > smallest_right)
            {
                return false;
            }
        }
    }

    return true;
}

void solve()
{
    int n;
    cin >> n;

    vector<double> position(n);
    for (double &val : position)
    {
        cin >> val;
    }

    vector<double> dress(n);
    for (double &val : dress)
    {
        cin >> val;
    }

    // if they can meet at some place in at most x minutes, they can meet at some place in at most y minutes for any y >= x; for x >= 0

    double left = 0;     // they cannot meet in 0 minutes
    double right = 1e20; // they will most certainly meet in this many minutes

    for (int index = 0; index < 1000; index++)
    {
        double mid = left + (right - left) / 2;
        if (canMeet(mid, position, dress))
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }

    cout << point(right, position, dress) << endl;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}