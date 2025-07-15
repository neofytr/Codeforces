#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<long long> labelToInteger(n + 1); // 1-based indexing
    unordered_map<long long, int> integerToCount;

    for (int index = 1; index <= n; index++)
    {
        cin >> labelToInteger[index];
        integerToCount[labelToInteger[index]]++;
    }

    long long maximum = LLONG_MIN;
    int location = 0;

    for (int index = 1; index <= n; index++)
    {
        if (integerToCount[labelToInteger[index]] == 1)
        {
            if (maximum < labelToInteger[index])
            {
                location = index;
                maximum = labelToInteger[index];
            }
        }
    }

    if (!location)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << location << endl;
    }
    return EXIT_SUCCESS;
}