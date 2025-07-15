#include <bits/stdc++.h>
using namespace std;

/*

to remove the lowest order set bit from a number num do ->
num = num & (num - 1)

*/

int main()
{
    long long num;
    cin >> num;

    // we want to count the number of ones in the binary representation of num
    int count = 0;
    while (num > 0)
    {
        count++;
        num &= (num - 1);
    }

    cout << count << endl;
    return EXIT_SUCCESS;
}