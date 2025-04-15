#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
    {
        cin >> val;
    }

    vector<int> prefix(n + 1, 0);
    for (int index = 1; index <= n; index++)
    {
        prefix[index] = prefix[index - 1] + arr[index - 1];
    }
}