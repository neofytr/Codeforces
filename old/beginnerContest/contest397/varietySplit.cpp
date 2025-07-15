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

    unordered_map<int, int> first; // map from element to it's count
    unordered_map<int, int> second;

    long long toRemove = 0;

    for (int index = 0; index < n; index++)
    {
        second[arr[index]]++;
    }

    int maximum = 0;

    for (int index = 0; index < n - 1; index++) // first contains upto index
    // second contains from index + 1 upto end
    {
        first[arr[index]]++;
        second[arr[index]]--;
        if (!second[arr[index]])
        {
            toRemove++;
        }

        int distOne = first.size();
        int distTwo = second.size() - toRemove;

        maximum = max(maximum, distOne + distTwo);
    }

    cout << maximum << endl;
}