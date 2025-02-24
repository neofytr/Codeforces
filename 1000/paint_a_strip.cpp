#include <iostream>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>

using namespace std;

int main()
{
    int t, n;
    cin >> t;

    for (int counter = 0; counter < t; counter++)
    {
        cin >> n;

        int delta = 1, count = 1;
        while (true)
        {
            if (delta >= n)
            {
                cout << count << endl;
                break;
            }

            count++;
            delta = 2 * (delta + 1);
        }
    }

    return EXIT_SUCCESS;
}