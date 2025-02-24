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
        vector<int> num(n);

        num[n - 1] = 6;

        if (n == 1)
        {
            cout << 6 << endl;
        }

        for (int counter = 0; counter < n - 1; counter++)
        {
            
        }
    }
}