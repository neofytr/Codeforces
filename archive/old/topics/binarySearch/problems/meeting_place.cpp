// https://codeforces.com/contest/782/problem/B

#include <bits/stdc++.h>
using namespace std;

bool canReach(double x, vector<double> &position, vector<double> &speed)
{
    // we need to check if they can reach a place in atmost x time

    double max_left = 1e-20;
    double min_right = 1e20;

    for (int index = 0; index < position.size(); index++)
    {
        double left = position[index] - speed[index] * x;
        double right = position[index] + speed[index] * x;

        max_left = max(max_left, left);
        min_right = min(min_right, right);

        if (min_right < max_left)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    int n;
    cin >> n;

    vector<double> position(n);
    for (double &val : position)
    {
        cin >> val;
    }

    vector<double> speed(n);
    for (double &val : speed)
    {
        cin >> val;
    }

    double left = 0;     // they cannot gather in atmost 0 time
    double right = 1e10; // they will gather in atmost this much time

    while (right - left > 1e-6)
    {
        double mid = left + (right - left) / 2;
        if (canReach(mid, position, speed))
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }

    cout << setprecision(12) << right << endl;
    return EXIT_SUCCESS;
}