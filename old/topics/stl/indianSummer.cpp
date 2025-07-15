#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<pair<string, string>> leaves;

    string species, color;
    for (int index = 0; index < n; index++)
    {
        cin >> species >> color;
        bool isUnique = true;
        if (index)
        {
            for (int counter = 0; counter <= index; counter++)
            {
                if (leaves[counter] == make_pair(species, color))
                {
                    isUnique = false;
                    break;
                }
            }

            if (isUnique)
            {
                leaves.push_back(make_pair(species, color));
            }

            continue;
        }

        leaves.push_back(make_pair(species, color));
    }

    cout << leaves.size() << endl;
    return EXIT_SUCCESS;
}