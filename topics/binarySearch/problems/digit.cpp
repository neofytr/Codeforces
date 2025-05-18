#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> q;

    while (q--)
    {
        long long k;
        cin >> k;

        long long start = 1;
        long long length = 1;
        long long count = 9;

        while (k > length * count) // strictly greater only
        {
            k -= count * length;
            start *= 10;
            length++;
            count *= 10;
        }

        long long number = start + (k - 1) / length;
        long long position = (k - 1) % length;

        string numStr = to_string(number);

        cout << numStr[position] << endl;
    }

    return 0;
}