#include <bits/stdc++.h>
using namespace std;

#define MAX_WEIGHT 1000000

int main()
{
    int n, w;
    cin >> n >> w;

    bitset<MAX_WEIGHT + 1> reachable;
    reachable[0] = true; // sum 0 is reachable (empty subset)

    int weight;

    for (int index = 0; index < n; index++)
    {
        cin >> weight;

        // update all reachable sums by weight
        reachable |= reachable << weight;
    }

    if (reachable[weight])
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }

    cout << endl;
    return EXIT_SUCCESS;
}