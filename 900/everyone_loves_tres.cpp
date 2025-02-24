#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

int even_sum(vector<int> &num)
{
    int sum;
    for (int counter = 0; counter < num.size(); counter += 2)
    {
        sum += num[counter];
    }

    return sum;
}

int odd_sum(vector<int> &num)
{
    int sum = 0;
    for (int counter = 1; counter < num.size(); counter += 2)
    {
        sum += num[counter];
    }

    return sum;
}

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
            num[counter] = 3;
        }
    }
}