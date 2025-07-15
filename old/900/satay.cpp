#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

int main()
{
    int t, n;

    cin >> t;
    while (t--)
    {
        cin >> n;
        vector<int> sticks(n);

        for (int counter = 0; counter < n; counter++)
        {
            cin >> sticks[counter];
        }

        int changes, index;
        do
        {
            index = 0;
            changes = 0;
            while (index < n - 1)
            {
                if (sticks[index] - sticks[index + 1] == 1)
                {
                    changes++;
                    swap(sticks[index], sticks[index + 1]);
                }

                index++;
            }
        } while (changes);

        bool sorted = true;
        for (index = 0; index < n - 1; index++)
        {
            if (sticks[index] > sticks[index + 1])
            {
                sorted = false;
                cout << "NO" << endl;
                break;
            }
        }

        if (sorted)
        {
            cout << "YES" << endl;
        }
    }
}