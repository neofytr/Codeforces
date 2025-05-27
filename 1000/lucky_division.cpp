#include <bits/stdc++.h>
using namespace std;

bool isAlmostLucky(int num)
{
    while (num > 0)
    {
        int dig = num % 10;
        if (dig != 4 && dig != 7)
        {
            return false;
        }

        num /= 10;
    }

    return true;
}

int main()
{
    int n;
    cin >> n;

    for (int div = 1; div <= n; div++)
    {
        if (isAlmostLucky(div))
        {
            if (!(n % div))
            {
                cout << "YES\n";
                return EXIT_SUCCESS;
            }
        }
    }

    cout << "NO\n";
    return EXIT_SUCCESS;
}
