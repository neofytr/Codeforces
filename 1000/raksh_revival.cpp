#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

int main()
{
    int t, n, m, k;
    cin >> t;

    while (t--)
    {
        cin >> n >> m >> k;
        vector<int> body(n);

        for (int &val : body)
        {
            cin >> val;
        }
    }
}