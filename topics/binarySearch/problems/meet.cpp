#include <bits/stdc++.h>
using namespace std;

bool canMeet(double time, vector<double> &position, vector<double> &dress, double &meetPoint)
{
    double leftBound = -1e18;
    double rightBound = 1e18;

    for (int i = 0; i < position.size(); i++)
    {
        if (time < dress[i])
            return false; 

        double reach = time - dress[i]; 
        double personLeft = position[i] - reach;
        double personRight = position[i] + reach;

        leftBound = max(leftBound, personLeft);
        rightBound = min(rightBound, personRight);

        if (leftBound > rightBound)
            return false; 
    }

    meetPoint = leftBound;
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

    double left = 0;    
    double right = 1e9; 
    double meetPoint = 0;

    for (int i = 0; i < 100; i++)
    {
        double mid = left + (right - left) / 2;
        double possibleMeetPoint;

        if (canMeet(mid, position, dress, possibleMeetPoint))
        {
            right = mid;
            meetPoint = possibleMeetPoint; 
        }
        else
        {
            left = mid;
        }
    }

    cout << fixed << setprecision(12) << meetPoint << endl;
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