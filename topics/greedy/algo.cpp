// https://vjudge.net/problem/Gym-102951B

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, x;
    cin >> n >> x;

    vector<int> arr(n);
    for (int &val : arr)
    {
        cin >> val;
    }
    sort(arr.begin(), arr.end());

    int count = 0;
    for (int index = 0; index < n; index++)
    {
        if (x > arr[index])
        {
            x -= arr[index];
            count++;
        }
        else
        {
            break;
        }
    }

    cout << count << endl;
    return EXIT_SUCCESS;
}