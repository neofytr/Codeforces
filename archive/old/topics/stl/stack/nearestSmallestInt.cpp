#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    // we'll use one-based indexing
    vector<int> arr(n + 1);
    for (int index = 1; index <= n; index++)
    {
        cin >> arr[index];
    }

    vector<int> ans(n + 1);

    for (int index = 1; index <= n; index++)
    {
        if (index == 1)
        {
            ans[index] = 0;
            cout << ans[index] << " ";
        }
        else
        {
            if (arr[index - 1] < arr[index])
            {
                ans[index] = index - 1;
                cout << ans[index] << " ";
            }
            else
            {
                int counter = ans[index - 1];
                bool done = false;
                while (counter)
                {
                    if (arr[counter] < arr[index])
                    {
                        ans[index] = counter;
                        cout << ans[index] << " ";
                        done = true;
                        break;
                    }
                    counter = ans[counter];
                }

                if (!done)
                {
                    ans[index] = 0;
                    cout << ans[index] << " ";
                }
            }
        }
    }

    cout << endl;

    return EXIT_SUCCESS;
}