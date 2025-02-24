#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int main()
{
    int t, n, k;
    cin >> t;

    for (int counter = 0; counter < t; counter++)
    {
        cin >> n >> k;
        vector<int> sorted(n);

        int num = 1;
        for (int &val : sorted)
        {
            val = num++;
        }

        int min = 0, max = n - 1;
    }
}