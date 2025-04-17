#include <bits/stdc++.h>
using namespace std;

int main()
{
    int val;
    vector<int> arr(14, 0); // 1-based indexing
    for (int index = 1; index <= 7; index++)
    {
        cin >> val;
        arr[val]++;
    }

    bool twoFound = false;
    bool threeFound = false;

    for (int index = 1; index <= 13; index++)
    {
        if (arr[index] == 2)
        {
            twoFound = true;
        }

        if (arr[index] == 3)
        {
            threeFound = true;
        }
    }

    if (twoFound && threeFound)
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }

    return EXIT_SUCCESS;
}