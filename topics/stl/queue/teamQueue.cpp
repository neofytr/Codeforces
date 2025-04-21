#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (true)
    {
        int t;
        cin >> t;
        if (!t)
        {
            return EXIT_SUCCESS;
        }

        unordered_map<int, int> mapping; // mapping element to it's team number
        // mapping to zero means isn't in any team

        int count;
        int member;
        for (int index = 1; index <= t; index++)
        {
            cin >> count;
            for (int counter = 0; counter < count; counter++)
            {
                cin >> member;
                mapping[member] = index; // set the member to its team
            }
        }
    }
}