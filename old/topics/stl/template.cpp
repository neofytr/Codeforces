#include <bits/stdc++.h>
using namespace std;

template <typename T>
T square(const T x)
{
    return x * x;
}

int main()
{
    int x;
    cin >> x;

    cout << square<int>(x);

    double y;
    cin >> y;

    cout << square<double>(x);
    return EXIT_SUCCESS;
}
