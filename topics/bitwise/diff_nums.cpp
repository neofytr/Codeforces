#include <bits/stdc++.h>
using namespace std;

#define MAX 1000000000

int main()
{
    long long n;
    cin >> n;

    vector<long long> arr(n);
    bitset<MAX> visited;

    for (long long &val : arr)
    {
        cin >> val;
    }

    for (long long index = 0; index < n; index++)
    {
        visited[index] = true;
    }

    cout << visited.count();
}