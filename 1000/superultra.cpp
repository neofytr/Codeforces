#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

using namespace std;

bool is_composite(int num)
{
    int till = (int)sqrt(num);
    for (int counter = 2; counter <= till; counter++)
    {
        if (!(num % counter))
        {
            return true;
        }
    }

    return false;
}

int main()
{
    int t, n;
    cin >> t;

    while (t--)
    {
        cin >> n;
        vector<int> arr(n);

        for (int index = 1; index <= n; index++)
        {
            arr[index - 1] = index;
        }

        bool found = false;
        do
        {
            bool no = false;
            for (int index = 0; index < n - 1; index++) // n is guaranteed to be greater than equal to 2
            {
                if (!is_composite(arr[index] + arr[index + 1]))
                {
                    no = true;
                    break;
                }
            }

            if (!no)
            {
                found = true;
                for (size_t i = 0; i < n; i++)
                {
                    cout << arr[i] << (i == n - 1 ? "\n" : " ");
                }
                break;
            }
        } while (next_permutation(arr.begin(), arr.end()));

        if (!found)
        {
            cout << -1 << "\n";
        }
    }
}