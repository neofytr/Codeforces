#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

void speedUpIO(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
}

int main()
{
    speedUpIO();
    int64_t t, n, k;

    cin >> t;
    for (int64_t counter = 0; counter < t; counter++)
    {
        cin >> n >> k;
        int64_t score = 0;
        vector<int64_t> arr(n);
        for (int64_t &val : arr)
        {
            cin >> val;
        }

        for (int64_t game = 0; game < n / 2; game++)
        {   
            
        }

        cout << score << endl;
    }
}