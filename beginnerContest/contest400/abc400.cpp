#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a;
    cin >> a;

    if (400 % a)
    {
        cout << -1 << endl;
        return EXIT_SUCCESS;
    }

    cout << 400 / a << endl;
    return EXIT_SUCCESS;
}