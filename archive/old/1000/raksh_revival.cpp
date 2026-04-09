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

        string s;
        cin >> s;

        vector<int> body(n);
        for (int i = 0; i < n; i++)
        {
            body[i] = s[i] - '0';
        }

        int timar = 0;
        int index = 0;
        int start = -1;

        while (index < n)
        {
            if (!body[index] && start == -1)
            {
                start = index;
            }

            if (body[index] && index - start < m && start != -1)
            {
                start = -1;
            }

            if (!body[index] && index - start + 1 == m && start != -1)
            {

                timar++;
                for (int counter = index; counter < index + k && counter < n; counter++)
                {
                    body[counter] = 1;
                }

                start = -1;
                index += k;
                continue;
            }

            index++;
        }

        cout << timar << endl;
    }
}