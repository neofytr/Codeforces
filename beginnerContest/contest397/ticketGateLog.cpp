#include <bits/stdc++.h>
using namespace std;

int main()
{
    string str;
    cin >> str;

    long long count = 0;
    for (int index = 0; index < str.length(); index++)
    {
        if (((index + 1) & 1) && str[index] != 'i')
        {
            str.insert(index, "i");
            count++;
        }

        if (!((index + 1) & 1) && str[index] != 'o')
        {
            str.insert(index, "o");
            count++;
        }
    }

    if (str.length() & 1)
    {
        str.insert(str.length(), "o");
        count++;
    }

    cout << count << endl;
    return EXIT_SUCCESS;
}