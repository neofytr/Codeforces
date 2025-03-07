#include <bits/stdc++.h>
using namespace std;

#define STRING_TO_FIND "string"

int main()
{
    string str;
    getline(cin, str);

    vector<size_t> positions;

    size_t pos = -1;
    while (pos != string::npos)
    {
        if (pos + 1 >= str.size())
        {
            break;
        }
        pos = str.find(STRING_TO_FIND, pos + 1);
        positions.push_back(pos);
    }

    cout << "Positions of \"" << STRING_TO_FIND << "\" in the string: ";
    for (size_t &val : positions)
    {
        cout << val << " ";
    }
    cout << endl;

    return EXIT_SUCCESS;
}